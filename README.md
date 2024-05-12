# Thermocouple

Easily obtain accurate temperature readings from various types of thermocouples using polynomial equations and Lookup Table methods, including cold junction compensation.

This C library streamlines the process of calculating precise thermocouple (TC) temperatures. Integration is straightforward, and a comprehensive example is provided in the `main.c` file for your convenience.

For detailed insights and usage instructions, refer to the following resources:

- **Reference:** Explore the methodology behind this library through the comprehensive documentation provided at [Mosaic Industries](http://www.mosaic-industries.com/embedded-systems/microcontroller-projects/microcontroller).
- **Tutorial Video:** Get started quickly by watching our instructional video on [YouTube](https://youtu.be/kuQf-JUNUAA).

## Notice

While this library is open-source and freely available, please exercise caution when integrating it into critical applications. While I strive for reliability, I cannot guarantee bug-free operation in all scenarios. Always verify its performance for your specific use case.

## To-Do List

- [x] Support Lookup Table functionality.
- [ ] Implement binary search algorithm for enhanced performance in Lookup Table mode.
- [ ] Extend thermocouple support to include additional types.
