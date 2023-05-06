# Catalogue

## Building
```bash
cmake -B build -G Ninja

make.bat
```

## Test
```bash
test.bat
```

## Performace 
```c++
Sample container    Data amount: 50000000
    Generation took: 6291.15[ms]

Default c++ std::find()
    find(container.begin(), container.end(), 512'321) took: 37.8101[ms]
    find(container.begin(), container.end(), 1) took: 8.6335[ms]
    find(container.begin(), container.end(), 12) took: 29.0318[ms]
    find(container.begin(), container.end(), 41'844'816) took: 30.7943[ms]
    find(container.begin(), container.end(), 12'312'312) took: 8.4021[ms]

catalogue::HashCatalogue
    Generation took: 25945.1[ms]
    catalogue.index<int>(512'321) took: 0.0015[ms]
    catalogue.index<int>(1) took: 0.0018[ms]
    catalogue.index<int>(12) took: 0.0009[ms]
    catalogue.index<int>(41'844'816) took: 0.0015[ms]
    catalogue.index<int>(12'312'312) took: 0.001[ms]

catalogue::TreeCatalogue
    Generation took: 164902[ms]
    catalogue.index<int>(512'321) took: 0.0039[ms]
    catalogue.index<int>(1) took: 0.0025[ms]
    catalogue.index<int>(12) took: 0.0019[ms]
    catalogue.index<int>(41'844'816) took: 0.0025[ms]
    catalogue.index<int>(12'312'312) took: 0.0018[ms]
```

## Benchmark
```bash
bench.bat
```
