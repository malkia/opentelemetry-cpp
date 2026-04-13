// clang-format off
#include <windows.h>
// clang-format on

#include <direct.h>
#include <processenv.h>
#include <atomic>
#include <cstdbool>
#include <future>
#include <optional>
#include <vector>

#include <absl/flags/flag.h>
#include <absl/flags/parse.h>
#include <tinyproc/process.hpp>

static std::atomic<bool> g_started;
static std::unique_ptr<TinyProcessLib::Process> g_otelcol_proc;
static std::unique_ptr<TinyProcessLib::Process> g_prometheus_proc;
static char g_workDir[1024]{};
static bool g_runPrometheus;

ABSL_FLAG(std::string, otelcol_binary, "", "Otelcol binary file");
ABSL_FLAG(std::string, otelcol_yaml, "", "Otelcol yaml file");
ABSL_FLAG(std::optional<std::string>, prometheus_binary, std::nullopt, "Prometheus binary file");
ABSL_FLAG(std::string, prometheus_yaml, "", "Prometheus yaml file");
ABSL_FLAG(std::string, test_binary, "", "Test binary file");
ABSL_FLAG(int, sleep, 10, "Additional sleep time");
ABSL_FLAG(bool, prometheus, false, "Run Prometheus");
ABSL_FLAG(bool, generate, false, "Generate metrics");

static void redirect_stdout(const char *bytes, size_t n)
{
  fwrite(bytes, 1, n, stdout);
}

static void redirect_stderr(const char *bytes, size_t n)
{
  fwrite(bytes, 1, n, stderr);
}

static std::unique_ptr<TinyProcessLib::Process> run_proc(const std::vector<std::string> &args,
                                                         bool customRedirect)
{
  TinyProcessLib::Config config;
  config.inherit_file_descriptors = true;
  // config.show_window = TinyProcessLib::Config::ShowWindow::force_minimize;
  return std::make_unique<TinyProcessLib::Process>(
      args, g_workDir, customRedirect ? redirect_stdout : nullptr,
      customRedirect ? redirect_stderr : nullptr, false, config);
}

static std::string get_dir(std::string name)
{
  const auto s1{name.rfind('\\')};
  const auto s2{name.rfind('/')};
  name.resize(
      (std::max)(s1 != std::string::npos ? s1 + 1 : 0, s2 != std::string::npos ? s2 + 1 : 0));
  return name;
}

int main(int argc, char *argv[])
{
  setvbuf(stdout, nullptr, _IONBF, 0);
  setvbuf(stderr, nullptr, _IONBF, 0);
  setvbuf(stdin, nullptr, _IONBF, 0);

  {
    // when running under bazel, this would be the source directory
    size_t x{};
    ::getenv_s(&x, g_workDir, "BUILD_WORKING_DIRECTORY");
  }

  absl::ParseCommandLine(argc, argv);

  const auto this_exe_dir{get_dir(argv[0])};
  const auto otelcol_exe{this_exe_dir + absl::GetFlag(FLAGS_otelcol_binary)};
  const auto otelcol_yaml{this_exe_dir + absl::GetFlag(FLAGS_otelcol_yaml)};
  const auto prometheus_exe{absl::GetFlag(FLAGS_prometheus_binary).has_value()
                                ? this_exe_dir + absl::GetFlag(FLAGS_prometheus_binary).value()
                                : ""};
  const auto prometheus_yaml{this_exe_dir + absl::GetFlag(FLAGS_prometheus_yaml)};

  printf("otelcol_exe=[%s]\n", otelcol_exe.c_str());
  printf("otelcol_yaml=[%s]\n", otelcol_yaml.c_str());
  printf("prometheus_exe=[%s]\n", prometheus_exe.c_str());
  printf("prometheus_yaml=[%s]\n", prometheus_yaml.c_str());
  printf("\n");

  int prometheusExitCode{};
  std::thread prometheus_thread{[&prometheus_exe, &prometheus_yaml, &prometheusExitCode]() {
    if (!prometheus_exe.empty())
    {
      printf("[STARTING] prometheus\n");
      g_prometheus_proc = run_proc(
          {prometheus_exe, "--web.enable-otlp-receiver", "--config.file", prometheus_yaml}, false);
      prometheusExitCode = g_prometheus_proc->get_exit_status();
      printf("[FINISHED] prometheus, exitCode=%d\n", prometheusExitCode);
    }
  }};

  int otelcolExitCode{};
  std::thread otelcol_thread{[&otelcol_exe, &otelcol_yaml, &otelcolExitCode]() {
    printf("[STARTING] otelcol\n");
    g_otelcol_proc  = run_proc({otelcol_exe, "--config", otelcol_yaml}, false);
    otelcolExitCode = g_otelcol_proc->get_exit_status();
    printf("[FINISHED] otelcol, exitCode=%d\n", otelcolExitCode);
  }};

  if (absl::GetFlag(FLAGS_generate))
  {
    while (g_otelcol_proc == nullptr || g_prometheus_proc == nullptr)
    {
      printf("*");  // fflush(stdout);
      std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));

    const auto test_exe{this_exe_dir + absl::GetFlag(FLAGS_test_binary)};
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
  }

  auto sleep = absl::GetFlag(FLAGS_sleep);
  printf("Sleeping for %d seconds...\n", sleep);
  std::this_thread::sleep_for(std::chrono::seconds(sleep));

  if (g_otelcol_proc)
    g_otelcol_proc->kill();

  if (g_prometheus_proc)
    g_prometheus_proc->kill();

  if (otelcol_thread.joinable())
    otelcol_thread.join();

  if (prometheus_thread.joinable())
    prometheus_thread.join();

  printf("END!\n");

  return 0;
}