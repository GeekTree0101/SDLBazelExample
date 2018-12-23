build:
	bazel build //Cube:CubeExample

run:
	bazel-bin/Cube/CubeExample

clean:
	bazel clean