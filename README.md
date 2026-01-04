# adas-soc-systems
This repository demonstrates the progression from modern C++ systems programming to Linux/QNX-based SoC platform software and ADAS system design, focusing on performance, safety, and real-world constraints.

adas-soc-systems/
│
├── README.md
│
├── 01_cpp_foundation/
│   ├── benchmarks/
│   │   ├── memory_layout.cpp
│   │   ├── cache_false_sharing.cpp
│   │   └── move_vs_copy.cpp
│   ├── concurrency/
│   │   ├── thread_pool/
│   │   ├── lock_free_ring_buffer/
│   │   └── producer_consumer/
│   └── notes/
│       └── cpp17_cpp20_decisions.md
│
├── 02_os_internals/
│   ├── linux/
│   │   ├── scheduler_notes.md
│   │   ├── irq_dma_flow.md
│   │   └── mmu_cache.md
│   └── qnx/
│       ├── msg_passing_demo/
│       ├── shared_memory_demo/
│       └── priority_inversion_test/
│
├── 03_soc_platform/
│   ├── boot_flow/
│   │   ├── rom_to_uboot.md
│   │   ├── uboot_config/
│   │   └── device_tree/
│   ├── drivers/
│   │   ├── fake_gpio_driver/
│   │   ├── fake_dma_driver/
│   │   └── mmio_register_map.h
│   └── bsp_minimal/
│       ├── toolchain/
│       ├── rootfs/
│       └── build_steps.md
│
├── 04_vehicle_services/
│   ├── someip/
│   │   ├── service_discovery/
│   │   └── client_server_demo/
│   ├── watchdog_health/
│   │   ├── heartbeat_service/
│   │   └── fault_injection/
│   └── ipc_comparison.md
│
├── 05_adas_pipeline/
│   ├── camera_simulator/
│   │   ├── frame_generator.cpp
│   │   └── latency_measurement.md
│   ├── isp_pipeline/
│   │   ├── raw_to_yuv.cpp
│   │   └── pipeline_arch.md
│   ├── sensor_fusion/
│   │   └── ekf_basics.md
│   └── failure_handling/
│       └── camera_failure_state_machine.md
│
├── 06_safety_security/
│   ├── secure_boot/
│   │   ├── signing_flow.md
│   │   └── rollback_strategy.md
│   ├── ota/
│   │   ├── update_sequence.md
│   │   └── failure_cases.md
│   └── iso_notes/
│       ├── iso26262_summary.md
│       └── iso21434_summary.md
│
├── 07_system_design/
│   ├── adas_ecu_design.md
│   ├── ota_at_scale.md
│   ├── soc_boot_time_optimization.md
│   └── power_dvfs_design.md
│
└── interviews/
    ├── cpp_questions.md
    ├── kernel_questions.md
    ├── system_design_questions.md
    └── self_introduction.md
