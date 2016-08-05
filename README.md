# unity-metadata-dumper (umd)

A utility for dumping the managed metadata of a Unity game built with IL2CPP.

## Usage

`umd` parses the `global-metadata.dat` file generated to emulate C# reflection
in C++. In Android apps, this file can be found at `assets\bin\Data\Managed\
Metadata\global-metadata.dat`.

1. Build `umd`:
    ```
    $ cmake -Bbuild -H.
    $ make -Cbuild
    ```

2. Run `umd`:
    ```
    $ ./build/umd /path/to/global-metadata.dat
    ```

## License

`umd` is released under the MIT License. See `LICENSE.txt` for more
information.

