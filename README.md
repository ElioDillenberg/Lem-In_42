# Lem-In (42 School Project)

Lem_in introduces the 42 students to the concept of graph traversal. The goal is to build a programm that will find the quickest way to get n ants accross an ant farm. 

In order to have an effective search that would both be fast in processing and give us the shortest possible path for any given ant farm we have chosen to use a BFS (Breadth First Search) coupled with DPF (Disjoint Path Finding).

Sources: http://www.macfreek.nl/memory/Disjoint_Path_Finding

The antfarm is provided by the user as follows:

<pre>
10 (number of ants in the starting room)
##start (following room is the starting room)
start 2 0 (declaration of a room, name = "start", x coordinate = 2, y coordinate = 0)
1 2 1
2 2 2
3 1 1
4 0 2
5 3 1
6 3 2
##end (following room is the end room)
end 2 3
start-1 (tunnel)
start-3
3-4
4-2
2-end
1-5
5-6
6-end
1-2
2-end
</pre>

NB: coordinates do not have an incident of the algorithm, it is only used in case students want to create a visualizer.

Graphical representation of this example : 

<pre>
      [start]
      /  |
   [3]  [1]---[5]
   /     |     |
[4]-----[2]   [6]
         |   /  
       [end]
</pre>

# How to run:
<pre>
git clone https://github.com/ElioDillenberg/Lem-In_42.git lem-in
cd lem-in
make
./lem-in < map_corr/classico.txt

usage: ./lem_in [option]
options:
    no option : lem_in works normally
    -rounds : displays the number of rounds
    -paths : displays used paths
    -duplicate : stop parsing if duplicate coordinates found
    -file -[path]: reads input from file at [path]

</pre>

The map_corr folder holds a few ant-farms, you can play around and build your own farms to test the program. 

Enjoy!

NB: The official project subject can be found as PDF in the subject folder.
