# Testing otel_sdk for real

- Go to the parent folder.
- Run `otel_sdk_build.cmd`
  * This would build the `otel_sdk.zip` file
- Unzip `otel_sdk.zip`
  * This would files over the `otel_sdk/<version>/...` folder
- Go back to the `otel_sdk` folder
- Run `bazel test ...`

## Notes

- Only Windows is supported for now.
