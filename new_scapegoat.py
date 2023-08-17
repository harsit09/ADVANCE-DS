    def insert(self, key):
        node = Node(key)
        #Base Case - Nothing in the tree
        if self.root == None:
            self.root = node
            return
        #Search to find the node's correct place
        currentNode = self.root
        while currentNode != None:
            potentialParent = currentNode
            if node.key < currentNode.key:
                currentNode = currentNode.left
            else:
                currentNode = currentNode.right
        #Assign parents and siblings to the new node
        node.parent = potentialParent
        if node.key < node.parent.key:
            node.parent.left = node
        else:
            node.parent.right = node
        node.left = None
        node.right = None
        self.size += 1
        #Finding the scapegoat
        scapegoat = self.findScapegoat(node)
        if scapegoat == None:
            return
        tmp = self.rebalance(scapegoat)

        #Assign the correct pointers to and from scapegoat
        scapegoat.left = tmp.left
        scapegoat.right = tmp.right
        scapegoat.key = tmp.key
        scapegoat.left.parent = scapegoat
        scapegoat.right.parent = scapegoat
