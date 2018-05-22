# SystemE
A game engine built(currently, but may change) on sfml

very incomplete engine, focused on the development of general 2D games.

Current To-Do:
- make console more sophisticated
- write script interface, audio, and graphical subsystems
- allow for either lua or lily scripts
- implement being able to read config files

Dependencies:
    SFML           - https://www.sfml-dev.org/
    GNU Readline   - to be deprecated
    Lua            - development libraries
    Lily(optional) - https://github.com/FascinatedBox/lily

Building:

in source dir type: cmake -H. -Bbuild

Running:

in source dir type: cmake --build build -- -j3

