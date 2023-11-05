# sports-data-analyzer
Analyzes sports data. Currently working on football data from Pro Football Reference.

# Dependencies
Outside of the C++ standard library, this project requires the following libraries to be installed:
```
curlpp // For getting sports data
curl // Dependency of curlpp
lexbor // For parsing HTML
```

# How To Build

To build, ensure you have the curlpp and curl libraries installed. Then, cd to the sports-data-analyzer directory run the following commands:
```
mkdir build
cd build
cmake ..
```

# How To Run

After building, make sure you are still in the build folder then run the following command:
```
./src/sports-data-analyzer.tsk
```
