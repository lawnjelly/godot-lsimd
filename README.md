# godot-simd
Godot module adding support for SIMD instructions from gdscript etc.

# About
This is a proof of concept module for high performance coding from gdscript and other scripting languages.

It adds a new class `FastArray_4f32`. This is an array made up of 4 32bit floats, corresponding to the `__m128` SSE type and `float32x4_t` in Neon.

You can use this array to perform basic math but considerably faster than gdscript would normally perform, I have profiled at approximately 400x faster.

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

  # perform SIMD function
	arr.add(Quat(1, 1, 1, 1), 0, size)

  # read
  var q : Quat
	for i in range (size):
		q = arr.read(i)
    # do something with q
```
