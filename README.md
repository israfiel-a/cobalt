![top_banner](https://github.com/israfiel-a/israfiel-a/blob/main/cobalt-banner.jpg)

---

### The Cobalt Operating System
Cobalt is an incredibly small, incredibly mediocre [x86_64](https://en.wikipedia.org/wiki/X86-64) operating system building mostly in [C23](https://en.wikipedia.org/wiki/C23_(C_standard_revision)). It's solely built to give me a better understanding of how operating systems get from bare(ish) hardware to advanced, multilayered software, and is as such meant for no real application in particular. I was deeply inspired by the [amazing work](https://templeos.org/) of [Mr. Terry Davis](https://en.wikipedia.org/wiki/Terry_A._Davis), alongside some other indie OS developers such as [Andreas Kling and his team](https://en.wikipedia.org/wiki/SerenityOS).

---

#### Dependencies
Cobalt depends on exactly nothing once compiled, besides (for now) a [UEFI-adherent firmware](https://en.wikipedia.org/wiki/UEFI) set. However, in order to compile, Cobalt requires an x86_64 [ELF](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format) version of [GCC](https://gcc.gnu.org/) and [Binutils](https://www.gnu.org/software/binutils/) (you can build those things [here](https://wiki.osdev.org/GCC_Cross-Compiler)). Its main build script is also in [CMake](https://cmake.org/), but that's not particularly hard to switch to something like [Ninja](https://ninja-build.org/).

> To build, simply run the `Build` script attached in a Bash-compatible shell session. If an error is thrown, please [open an issue](https://github.com/israfiel-a/cobalt/issues), regardless of whether you managed to fix the issue or not.

---

#### Philosophy
Now, I ain't one of them holier-than-thou C purists who believes strictly in the [Un*x](https://en.wikipedia.org/wiki/Unix) philosophies as if from the mouth of God himself, but I do hold myself to standards. This project is not to rely on external libraries, beyond those provided by firmware. All code taken from another source is to be documented in the [`CREDITS.md`](./CREDITS.md) file, with detailed links and line numbers for each sample. This operating system will not become shovelware; on every release, all code should be expected to be the best I can make it. No half measures.

Much love, and welcome to Cobalt.

---

![bottom_banner](https://github.com/israfiel-a/israfiel-a/blob/main/cobalt-banner.jpg)