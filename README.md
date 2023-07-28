# LuxeOS

## Building & Running

After cloning this repo, run `./configure` to automatically generate a Makefile.
Alternatively, you can run `./configure help` to see customizable options.

If you wish to customize the build in any way, you can use `make menuconfig` or `make guiconfig`.
Otherwise, run `make`.

To run Luxe in QEMU, run `make run`.

# Contributing

Contributions are always welcome in the form of bug fixes, improvements and bug reports.

Feature requests also might be considered.

Before submitting a PR, make sure you run `make format` to format your code to fit the LuxeOS standards. Failure to do so will result in your PR not being merged.

Before filing a bug report, make sure you send all required information
> [!IMPORTANT]
> Fairly incomplete issues will be closed immediately.

Although not required, you are encouraged to follow the issue template to solve the issue quickly.

## License

<img src="https://upload.wikimedia.org/wikipedia/commons/f/f0/CC_BY-ND.svg" width="229" height="80">

This project is licensed under the CC BY-ND 4.0 license, which you can find [here](LICENSE.md).