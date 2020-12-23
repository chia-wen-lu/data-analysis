## Team assignment for Data Structure in C

------------




#### Teammate:
- 408415035 盧佳玟
- 408415049 施湘芸
- 408415055 朱沛哲
- 408415057 郭宗翰

#### Topic
> Connect three assembly lines and a cargo line in the factory ,there will have a material entered into the machine with a random time,different assembly line has different deal time.If the last material hasn’t finish,next material need to wait in line.Some emergency material can cut in line.We should output all the items waiting or processing at which assembly line per second.


#### Project Goal
+ to understand the concept of queues
+ to design operations associated to queues
+ to implement the operations to realize ADT concept

#### Structure Chart
+ Factory
	- node
		* item
		* type
		* arrival time
	- Q
		* item
		* count
		* create list
			+ enqueue(enQ)
			+ dequeue(deQ)

>In main function,there will have a large timer which is design by loop,wether enqueue and dequeue
will be put into the timer.
#### Data Structure
```C
typedef struct node		// the type of list
{
	char item[10];
	int type;
	int arrival_time;
	struct node *next;
}dType;

typedef struct Q
{
	int count;
	struct node * left , * right;
}qType;

```


#### License
```
Copyright (c) 2020 chiawenlu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```