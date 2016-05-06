{
  "targets": [
    {
      "target_name": "trace_native",
      "sources": [
        "./src/trace_module.cc",
        "./src/trace_broker.cc",
        "./src/trace_console_listener.cc",
        "./src/diag_utils.cc"
      ],
      "include_dirs": [
        "./src",
      ]
    }
  ]
}
