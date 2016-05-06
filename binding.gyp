{
  "targets": [
    {
      "target_name": "trace_native",
      "sources": [
        "./src/trace_module.cc",
        "./src/trace_broker.cc",
        "./src/diag_utils.cc"
      ],
      "include_dirs": [
        "./src",
        "./third_party/json/src"
      ]
    }
  ]
}
