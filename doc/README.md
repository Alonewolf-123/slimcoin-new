Slimcoin 0.10.0 BETA

Setup
---------------------
Slimcoin is the original Slimcoin client and it builds the backbone of the network. It downloads and, by default, stores the entire history of Slimcoin transactions (which is currently less than one gigabyte); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download Slimcoin, visit [slimcoin.net](https://slimcoin.net/download).

Running
---------------------
The following are some helpful notes on how to run Slimcoin on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/slimcoin-qt` (GUI) or
- `bin/slimcoind` (headless)

### Windows

Unpack the files into a directory, and then run slimcoin-qt.exe.

### macOS

Drag Slimcoin to your applications folder, and then run Slimcoin.

### Need Help?

* See the documentation at the [Slimcoin Wiki](https://docs.slimcoin.net/)
for help and more information.
* Slimcoin is very similar to bitcoin, so you can use their wiki [Bitcoin Wiki](https://en.bitcoin.it/wiki/Main_Page).
* Ask for help on [#general](https://slimcoin.chat/) on slimcoin.chat.

Building
---------------------
The following are developer notes on how to build Slimcoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [FreeBSD Build Notes](build-freebsd.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [NetBSD Build Notes](build-netbsd.md)
- [Gitian Building Guide (External Link)](https://github.com/bitcoin-core/docs/blob/master/gitian-building.md)

Development
---------------------
The Slimcoin repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Productivity Notes](productivity.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](none-yet)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [JSON-RPC Interface](JSON-RPC-interface.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [Slimcoin](https://talk.slimcoin.net/) forums.

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [bitcoin.conf Configuration File](bitcoin-conf.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Memory](reduce-memory.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)
- [PSBT support](psbt.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
