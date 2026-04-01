#include <reproc++/drain.hpp>
#include <reproc++/reproc.hpp>

#include <atomic>
#include <cstdbool>
#include <future>

std::atomic<bool> g_stop;

int run_proc(const std::string &exe, const std::vector<std::string> &arguments)
{
  std::vector<const char *> args;

  args.push_back(exe.c_str());
  for (const auto &arg : arguments)
    args.push_back(arg.c_str());
  args.push_back(nullptr);

  reproc::process proc;
  reproc::options opts;
  opts.stop = {{reproc::stop::terminate, reproc::milliseconds(1000)},
               {reproc::stop::kill, reproc::milliseconds(500)},
               {}};

  {
    const auto ec{proc.start(args.data(), opts)};
    if (ec)
    {
      printf("ERROR: %s\n", ec.message().c_str());
      return ec.value();
    }
  }

  std::mutex mutex;

  std::string stdout_buf;
  std::string stderr_buf;

  const auto flush{[&stdout_buf, &stderr_buf, &mutex, &proc, &opts] {
    std::lock_guard<std::mutex> lock(mutex);

    fputs(stdout_buf.c_str(), stdout);
    fputs(stderr_buf.c_str(), stderr);
    stdout_buf.clear();
    stderr_buf.clear();
    fflush(stdout);
    fflush(stderr);
  }};

  auto drain_async{std::async(std::launch::async, [&proc, &stdout_buf, &stderr_buf, &mutex] {
    reproc::sink::thread_safe::string sink_stdout(stdout_buf, mutex);
    reproc::sink::thread_safe::string sink_stderr(stderr_buf, mutex);
    return reproc::drain(proc, sink_stdout, sink_stderr);
  })};

  while (drain_async.wait_for(std::chrono::milliseconds(1)) != std::future_status::ready)
  {
    flush();
    if (g_stop)
    {
      printf("Aborting...\n");
      //    proc.terminate();
      proc.kill();
      printf("Killed...\n");
      return 0;
    }
  }
  flush();

  auto ec{drain_async.get()};
  if (ec)
  {
    printf("ERROR: %s\n", ec.message().c_str());
    return ec.value();
  }

  int status{};
  std::tie(status, ec) = proc.stop(opts.stop);
  if (ec)
  {
    printf("ERROR: %s\n", ec.message().c_str());
    return ec.value();
  }
  return status;
}

std::string get_dir(std::string name)
{
  const auto s1{name.rfind('\\')};
  const auto s2{name.rfind('/')};
  name.resize(
      (std::max)(s1 != std::string::npos ? s1 + 1 : 0, s2 != std::string::npos ? s2 + 1 : 0));
  return name;
}

int main(int argc, const char *argv[])
{
  if (argc != 4 )
    perror("exactly 3 arguments expected");

  setvbuf(stdout, nullptr, _IONBF, 0);
  setvbuf(stderr, nullptr, _IONBF, 0);
  const auto this_exe_dir{get_dir(argv[0])};
  const auto otelcol_exe{this_exe_dir + std::string(argv[1])};
  const auto otelcol_yaml{this_exe_dir + std::string(argv[2])};
  printf("otelcol_exe=[%s]\n", otelcol_exe.c_str());
  printf("otelcol_yaml=[%s]\n", otelcol_yaml.c_str());
  printf("\n");
  fflush(stdout);

  int otelcolExitCode{};
  std::thread otelcol_thread{[&otelcol_exe, &otelcol_yaml, &otelcolExitCode]() {
    otelcolExitCode = run_proc(otelcol_exe, {"--config", otelcol_yaml});
    printf("[FINISHED] otelcol\n");
    fflush(stdout);
  }};

  if( argv[3][0] >= '0' && argv[3][0] <= '9' )
  {
    auto sleep = std::stoi(argv[3]);
    printf("Sleeping for %d seconds...\n", sleep);
    std::this_thread::sleep_for(std::chrono::seconds(sleep));
  }   
  else
  {
    std::this_thread::sleep_for(std::chrono::seconds(3));

    const auto test_exe{this_exe_dir + std::string(argv[3])};
    printf("\ntest_exe=[%s]\n\n", test_exe.c_str());
    fflush(stdout);
    std::vector<std::thread> threads;
    threads.reserve(100);

    for (int i = 0; i < 10; i++)
    {
      int testExitCode{};
      threads.emplace_back([&test_exe, &testExitCode, i=i]() {
        testExitCode = run_proc(test_exe, {});
        printf("[FINISHED] test %d\n", i);
        fflush(stdout);
      });
    }

    for(auto& thread : threads )
      if (thread.joinable())
        thread.join();

    std::this_thread::sleep_for(std::chrono::seconds(2));
  }


  g_stop = true;
  printf("END!\n");
  // if (otelcol_thread.joinable())
  //   otelcol_thread.join();

  // if( otelcolExitCode )
  //   return otelcolExitCode;

  // if( testExitCode )
  //   return testExitCode;

  return 0;
}