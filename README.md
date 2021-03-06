# Fork

```
git submodule add https://github.com/arcchang1236/Allegro-5 
```

# Xcode

Create a new Xcode project

* Select `Cocoa App` (under the `macOS` tab) [ Next ]
* Input Product Name `allegro-exercise`, Select Language `Objective-C` [ Next ]

Post-Create

* Delete file `AppDelegate.h` [ Move to Trash ]
* Delete file `AppDelegate.m` [ Move to Trash ]
* Delete file `ViewController.h` if exists [ Move to Trash ]
* Delete file `ViewController.m` if exists [ Move to Trash ]
* Delete file `main.m` if exists [ Move to Trash ]
* Go to `Build Settings` :: `All`
* Find `Header Search Paths`, then double click on it. Press the `+` and type `/usr/local/include`, change `non-recursive` to `recursive`
* Find `Library Search Paths`, then double click on it. Press the `+` and type `/usr/local/include`, change `non-recursive` to `recursive`
* Find `C++ Language dialect`, then turn it into `into GNU++11`

Open a terminal

```
cd /usr/local/Cellar
open .
```

Enter `allegro` :: `5.2.3.0` :: `lib`

Sort by `Date Modified` in `desc` order

Choose the files that modified `today`

Go back to Xcode, find `General`

Move all the selected file to `Linked Frameworks and Libraries`

Go to `Build phases`, then press the `+` and choose `New Copy Files Phase`

Find `Copy Files`, then change Destination from `Resources` to `Frameworks`. Then drag the files you selected before to here and choose `Create groups`.

# main.cpp

Find `allegro-exercise`

Right click to add new file, then choose `C++ File` and type Name `main.cpp`

See `examples/1/main.cpp`

Press `Build and then run the current scheme`

You should see a window filled with purple color.

# Final Project

Delete file `main.cpp` [ Move to Trash ]

Delete file `main.hpp` [ Move to Trash ]

Find `allegro-exercise`

Method 1

```
Right click, then choose `Add Files to "allegro-exercise"`

Navigate to `Allegro-5/template/code/`, then select all files
```

Method 2

```
cp Allegro-5/template/code/* allegro-exercise/allegro-exercise/

Right click, then choose `Add Files to "allegro-exercise"`

Navigate to `allegro-exercise/allegro-exercise/`, then select all files
```

Press `Build and then run the current scheme`

You should see a game window with background music.

