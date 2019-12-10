# godot-simd
Godot module adding support for SIMD instructions from gdscript etc.

# About
This is a proof of concept module for high performance coding from gdscript and other scripting languages.

It adds a new class `FastArray_4f32`. This is an array made up of 4 32bit floats, corresponding to the `__m128` SSE type and `float32x4_t` in Neon. Instead of having a loop in gdscript and calling a function multiple times, instead here the math functions take a `from` and `to` argument to pass the array range to apply the function to. 

You can use this array to perform basic math but considerably faster than gdscript would normally perform, I have profiled at usually between 100x and 1000x faster.

The speedup is due to:
1) Linear ideally packed aligned layout in memory
2) Designed for easy compiler optimization
3) Autovectorization to SSE or Neon instructions where available

# ToDo
I have started making optional SSE versions of the functions. There is CPU detection code to detect CPU caps at startup, and dynamic dispatch to the fastest path supported by the hardware. The SSE code can be compiled out by switching out defines.

# Functions
Functions include:
* read / writing elements and reserving array
* read / writing as pool arrays
* add, subtract, multiply, divide
* sqrt, inverse sqrt, reciprocal
* vec3: dot, cross, unit cross, normalize
* vec3: length, length squared
* vec3: xform, inverse xform

# Example
```
const size = 5000000

func TestSIMD():

	# create SIMD array
	var arr = FastArray_4f32.new()
	arr.reserve(size)

	# fill
	for i in range (size):
		arr.write(i, Quat(1, 1, 1, 1))

	# perform ranged function (single instruction, multiple data)
	arr.value_add(Quat(1, 1, 1, 1), 0, size)

	# read
	var q : Quat
	for i in range (size):
		q = arr.read(i)
		# do something with q
```

# ToDo
* Thread safety
* Alignment
* Strided generic versions of functions (for use on external arrays)

# Notes
As yet some operations are difficult / impossible to autovectorize and require compiling without disabling intrinsics for maximum speed. These include sqrt, inverse sqrt and operations which depend on these.
