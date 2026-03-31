#include <reproc++/drain.hpp>
#include <reproc++/reproc.hpp>
#include <future>

int run_proc(const std::string &exe, const std::vector<std::string> &arguments)
{
  std::vector<const char *> args;

  args.push_back(exe.c_str());
  for (const auto &arg : arguments)
    args.push_back(arg.c_str());
  args.push_back(nullptr);

  reproc::process proc;
  reproc::options opts;
  opts.stop = {{reproc::stop::terminate, reproc::milliseconds(5000)},
               {reproc::stop::kill, reproc::milliseconds(2000)},
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

  const auto flush{[&stdout_buf, &stderr_buf, &mutex] {
    std::lock_guard<std::mutex> lock(mutex);
  
    fputs(stdout_buf.c_str(), stdout);
    fputs(stderr_buf.c_str(), stderr);
    stdout_buf.clear();
    stderr_buf.clear();
  }};

  auto drain_async{std::async(std::launch::async, [&proc, &stdout_buf, &stderr_buf, &mutex] {
    reproc::sink::thread_safe::string sink_stdout(stdout_buf, mutex);
    reproc::sink::thread_safe::string sink_stderr(stderr_buf, mutex);
    return reproc::drain(proc, sink_stdout, sink_stderr);
  })};

  while (drain_async.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready)
    flush();
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
  if (argc != 2)
    perror("exactly one argument expected");
  const auto this_exe_dir{get_dir(argv[0])};
  const auto otelcol_exe{this_exe_dir + std::string(argv[1])};
  printf("[%s]\n", otelcol_exe.c_str());

  return run_proc(otelcol_exe, {"help", "print-config"});
}