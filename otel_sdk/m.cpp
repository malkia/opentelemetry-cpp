#include <windows.h>
#include <direct.h>
#include <processenv.h>
#include <atomic>
#include <cstdbool>
#include <future>
#include <optional>
#include <vector>

#include <tinyproc/process.hpp>

static std::atomic<bool> g_started;
static std::unique_ptr<TinyProcessLib::Process> g_otelcol_proc;
static char g_sourceDir[1024]{};

static void redirect_stdout(const char *bytes, size_t n)
{
  fwrite(bytes, 1, n, stdout);
}

static void redirect_stderr(const char *bytes, size_t n)
{
  fwrite(bytes, 1, n, stderr);
}

static std::unique_ptr<TinyProcessLib::Process> run_proc(const std::vector<std::string> &args, bool customRedirect)
{
  TinyProcessLib::Config config;
  config.inherit_file_descriptors = true;
  // config.show_window = TinyProcessLib::Config::ShowWindow::force_minimize;
  return std::make_unique<TinyProcessLib::Process>(args, g_sourceDir,
                                                   customRedirect ? redirect_stdout : nullptr,
                                                   customRedirect ? redirect_stderr : nullptr,
                                                   false, config);
}

static std::string get_dir(std::string name)
{
  const auto s1{name.rfind('\\')};
  const auto s2{name.rfind('/')};
  name.resize(
      (std::max)(s1 != std::string::npos ? s1 + 1 : 0, s2 != std::string::npos ? s2 + 1 : 0));
  return name;
}

int main(int argc, const char *argv[])
{
  setvbuf(stdout, nullptr, _IONBF, 0);
  setvbuf(stderr, nullptr, _IONBF, 0);
  setvbuf(stdin, nullptr, _IONBF, 0);

  {
    // when running under bazel, this would be the source directory
    size_t x{};
    ::getenv_s(&x, g_sourceDir, "BUILD_WORKING_DIRECTORY");
  }

  if (argc != 4)
  {
    perror("exactly 3 arguments expected");
    return 1;
  }

  const auto this_exe_dir{get_dir(argv[0])};
  const auto otelcol_exe{this_exe_dir + std::string(argv[1])};
  const auto otelcol_yaml{this_exe_dir + std::string(argv[2])};

  printf("otelcol_exe=[%s]\n", otelcol_exe.c_str());
  printf("otelcol_yaml=[%s]\n", otelcol_yaml.c_str());
  printf("\n");

  int otelcolExitCode{};
  std::thread otelcol_thread{[&otelcol_exe, &otelcol_yaml, &otelcolExitCode]() {
    printf("[STARTING] otelcol\n");
    g_otelcol_proc  = run_proc({otelcol_exe, "--config", otelcol_yaml}, false);
    otelcolExitCode = g_otelcol_proc->get_exit_status();
    printf("[FINISHED] otelcol, exitCode=%d\n", otelcolExitCode);
  }};

  if (argv[3][0] >= '0' && argv[3][0] <= '9')
  {
    auto sleep = std::stoi(argv[3]);
    printf("Sleeping for %d seconds...\n", sleep);
    std::this_thread::sleep_for(std::chrono::seconds(sleep));
  }
  else
  {
    while (g_otelcol_proc == nullptr)
    {
      printf("*");  // fflush(stdout);
      std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    const auto test_exe{this_exe_dir + std::string(argv[3])};
    printf("\ntest_exe=[%s]\n\n", test_exe.c_str());

    std::vector<std::thread> threads;
    threads.reserve(100);
    for (int i = 0; i < 10; i++)
    {
      int testExitCode{};
      threads.emplace_back([&test_exe, &testExitCode, i = i]() {
        auto p        = run_proc({test_exe}, true);
        auto exitCode = p->get_exit_status();
        printf("[FINISHED] test %d (%d)\n", i, exitCode);
      });
    }

    for (auto &thread : threads)
      if (thread.joinable())
        thread.join();

    std::this_thread::sleep_for(std::chrono::seconds(3));
  }

  if (g_otelcol_proc)
    g_otelcol_proc->kill();

  printf("END!\n");

  return 0;
}