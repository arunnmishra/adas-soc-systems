# adas-soc-systems
This repository demonstrates the progression from modern C++ systems programming to Linux/QNX-based SoC platform software and ADAS system design, focusing on performance, safety, and real-world constraints.


adas-soc-systems/
│
├── README.md
│
├── 01_cpp_foundation/
│   ├── benchmarks/
│   │   ├── memory_layout.cpp
│   │   ├── padding_alignment.cpp
│   │   ├── move_vs_copy.cpp
│   │   ├── rvo_test.cpp
│   │   └── const_correctness.cpp
│   │
│   ├── concurrency/
│   │   ├── raii_resource.cpp
|   |   |── custom_pool.cpp
│   │   └── ownership_examples.cpp
│   │
│   ├── notes/
│   │   ├── week1_observations.md
│   │   ├── month1_summary.md
│   │   └── cpp_design_principles.md
│
├── 02_service_framework/              ← starts Week 2/3 (separate on purpose)
│   ├── core/
│   │   ├── service_id.h
│   │   ├── message.h
│   │   ├── buffer.h
│   │   ├── message_envelope.h
│   │   └── publisher.h
│   │
│   ├── examples/
│   │   ├── single_service_demo.cpp
│   │   └── ownership_transfer_demo.cpp
│   │
│   ├── docs/
│   │   ├── design_goals.md
│   │   ├── threading_model.md
│   │   └── why_not_someip.md
│   │
│   └── README.md
│
├── 03_os_internals/
│   ├── linux/
│   │   ├── boot_flow.md
│   │   ├── scheduler_notes.md
│   │   ├── mmu_cache.md
│   │   └── irq_dma_flow.md
│   │
│   ├── qnx/
│   │   ├── msg_passing_demo/
│   │   ├── shared_memory_demo/
│   │   └── priority_inversion_test/
│   │
│   └── notes/
│       └── linux_vs_qnx.md
│
├── 04_soc_platform/
│   ├── boot_flow/
│   │   ├── rom_to_uboot.md
│   │   ├── uboot_config/
│   │   └── device_tree/
│   │
│   ├── drivers/
│   │   ├── fake_gpio_driver/
│   │   ├── fake_dma_driver/
│   │   └── mmio_register_map.h
│   │
│   ├── bsp_minimal/
│   │   ├── toolchain/
│   │   ├── rootfs/
│   │   └── build_steps.md
│   │
│   └── notes/
│       └── soc_enablement_basics.md
│
├── 05_vehicle_services/
│   ├── someip/
│   │   ├── service_discovery/
│   │   └── client_server_demo/
│   │
│   ├── watchdog_health/
│   │   ├── heartbeat_service/
│   │   └── fault_injection/
│   │
│   └── ipc_comparison.md
│
├── 06_adas_pipeline/
│   ├── camera_simulator/
│   │   ├── frame_generator.cpp
│   │   └── latency_measurement.md
│   │
│   ├── isp_pipeline/
│   │   ├── raw_to_yuv.cpp
│   │   └── pipeline_arch.md
│   │
│   ├── sensor_fusion/
│   │   └── ekf_basics.md
│   │
│   └── failure_handling/
│       └── camera_failure_state_machine.md
│
├── 07_safety_security/
│   ├── secure_boot/
│   │   ├── signing_flow.md
│   │   └── rollback_strategy.md
│   │
│   ├── ota/
│   │   ├── update_sequence.md
│   │   └── failure_cases.md
│   │
│   └── iso_notes/
│       ├── iso26262_summary.md
│       └── iso21434_summary.md
│
├── 08_system_design/
│   ├── adas_ecu_design.md
│   ├── ota_at_scale.md
│   ├── soc_boot_time_optimization.md
│   └── power_dvfs_design.md
│
└── interviews/
    ├── cpp_questions.md
    ├── kernel_questions.md
    ├── soc_questions.md
    ├── system_design_questions.md
    └── self_introduction.md
