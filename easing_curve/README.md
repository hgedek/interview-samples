#Introduction

Hello,

this sample is developed for an interview exercise. It aims to solve some easing curve equations and to output their results.

Equations re used from this website :https://www.gizma.com/easing/ 

## Bulding

create build dir under easing_curve

mkdir build
cd build
cmake .. -DTESTING=OFF
make

it will create output under ../bin folder

## Running

samples re put under 'input' folder... we can pass those files as arg:

./bin/easing_curve one_curve.txt

or we can use absolute path:

./bin/easing_curve .../.../.../one_curve.txt abs


## Testing

create a build folder in easing_curve 

cd build
cmake .. -DTESTING=ON
make

this will create testing binary under bin also tests will be run while building


## Possible Bugs

I assumed all input data formats as:

```
Linear,x_t0=100,x_tmax=200,duration=1
0.2
0.5
1.0

```

