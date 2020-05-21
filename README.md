# **visualizations_audialization**

### **Command Line arguments:**
Usage: AudialVisualization [OPTION...]

--help                       print help

-a, --audial                 play audialization using TSAL

-v, --visual                 show visualization using TSGL

-h, --canvas-height arg      TSGL canvas height (default: 1024 or 512 if sorting algorithm)

-w, --canvas-width arg       TSGL canvas width (default: 1024)

-d, --data-amount arg        Number of data elements to sort. Only used when inheriting from SortingAudialVisualization. This            parameter must be less than or equal to canvas-width.

-t, --threads arg            number of threads to use for sorting algorithm (default: 1)

-s, --sorting-algorithm arg  decide which sorting algorithm to run (argument options: 'bubble', 'insertion', 'merge', 'selection', 'shaker')


# **Dependencies**
- [TSGL](https://github.com/Calvin-CS/TSGL)

- [TSAL](https://github.com/Calvin-CS/TSAL)

- [CXXOPTS](https://github.com/jarro2783/cxxopts)
