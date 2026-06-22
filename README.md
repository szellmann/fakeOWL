fake[Owl](https://github.com/owl-project/owl)
===========

A CPU implementation of OWL. Very experimental :-)

CPU intersections are computed using the [Visionaray](https://github.com/szellmann/visionaray) submodule, but honestly, intersections make up for less than 1% of this library. We could probably use Embree here w/o much effort, but I'm using Visionaray b/c it comes with a nice texture abstraction layer, and I'm also more familiar with Visionaray than with Embree, so I never bothered to replace it so far.

Porting existing OWL code
-------------------------

I'm currently only supporting a subset of OWL and adding features only as needed for my own projects. Also note that OWL CPU programs are pretty slow due to certain conceptual limitations (mostly function call overhead and costly access to TLS). So it's mostly useful for debugging and similar.

The following changes are necessary to an existing code base at the very least:

Replace `owlXXXBufferCreate()` with `owlBufferCreateEXT()` from [owl_ext.h](/include/owl/owl_ext.h) (uses malloc/free instead of cudaMalloc et al.).

The device code _should_ mostly just work. See the comments on CUDA below, and it _might_ be necessary to shuffle some headers around in case that declarations are slightly different than in _real_ OptiX.
In your "device code":

CMake is a bit different of course. You have to link with libfakeOwl.{a|dylib} and you want to check out the macro `fake_owl_compile_and_embed` in [cmake/configure_fake_owl.cmake](/cmake/configure_fake_owl.cmake). With my cmake version (3.19.1) that macro would fail if being passed `.cu` files, therefore I'm renaming the files where the optix device programs would usually go to `.cpp` (another option would be to use symlinks).

That's mostly it. _Some_ platform-specific CUDA stuff works, but most (obviously) doesn't. Have a look at the [fake/cuda.h](/include/owl/fakeOwl/fake/cuda.h) and [fakeOwl/optix.h](/include/owl/fakeOwl/fake/optix.h) files. The OptiX functions should _eventually_ be ported in their entirety but the CUDA stuff is only there for convenience. BTW, there is a `clock64()` implementation in `fake/cuda.h` that you should use instead of `clock()` on x86, as the latter will perform syscalls and is awfully slow (some of the owl samples use `clock()`).

OWL compatibility
-----------------

fakeOwl tracks stable OWL releases; the basis for new fakeOwl versions form the public header files under [include/owl/](https://github.com/NVIDIA/OWL/tree/main/include/owl). The current fakeOwl version is based on the commit `c1c296c5c7dc00691c309ea4c609797e1bde8c49` (OWL main as of Wed Jun 17 12:28:56 2026 -0600). See [fake/version.h](/include/owl/fakeOwl/fake/version.h) for details.

License
-------

Apache 2 if not noted otherwise. I'm including lot's of code that was directly copied from OWL, whose license is also Apache 2.

