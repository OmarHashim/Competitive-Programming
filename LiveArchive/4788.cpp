/*
    we will brute force the starting node 
    we call dfs from starting node and for each node we calculate 2 values, minimum no. of soliders that are needed to conquer it's entire
    subtree , and how many of them will return ( dont die or have to stay) after all the subtree is conquered.
    for a leaf node, mnSoldier[i]=max(a[i],m[i]+g[i]) , returning=mnSoldier[i]-m[i]-g[i]
    we initialize answer for non leaf nodes the same way, then we make a vector of pairs that store the values for all children
    then we sort the vector by no. of returning soldiers in decreasing order and we visit the children in that order
    that way we can make use of the returning soliders from some child in the following children
*/

// unfortunately lost the code
