#! /usr/bin/python3

'''
 Given the root to a binary tree, implement serialize(root), which serializes the tree into a string,
 and deserialize(s), which deserializes the string back into the tree.
 
 For example, given the following Node class
 
  class Node:
      def __init__(self, val, left=None, right=None):
          self.val = val
          self.left = left
          self.right = right
 
 The following test should pass:
 
  node = Node('root', Node('left', Node('left.left')), Node('right'))
  assert deserialize(serialize(node)).left.left.val == 'left.left'
'''
 

class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def serialize(root_node, mode=0):
    # Given that this is python, the *easy* way to do this is just to 
    # generate __repr__ methods and serialize those.
    # Deserialization, then, would be be to simply evaluate this expression, as it
    # will be valid python.
    #
    # The trickiest part of any serialization would be properly handling termination
    # of values. E.G., we'd need to know how to serialize the value itself, and
    # if it contains string data (which the examples do), then we need to be able
    # to terminate this strings. This can be particularly annoying because strings can
    # contain anything else, including escape characters that can mess with trivial
    # couting.

    def repr_node_verbose(node):
        ''' This works by recursively generating a repr string of the nodes and their values.
        The caveat is that it will put None in place for Left and Right nodes, even when
        that's implied, wasting space. However, this may be faster.
        '''
        if node is not None:
            return f'Node({repr(node.val)}, {repr_node_verbose(node.left)}, {repr_node_verbose(node.right)})'

    def repr_node_explicit(node):
        ''' This works by recursively generating a repr string of the nodes and their values.
        If a child node is None, then we'll end up skipping it.
        The caveat is that we will always explicitly call out the keyword arg names, meaning serialization
        may be larger for fully formed nodes. However, this has the benefits that if the API changes to switch
        the order, then the serialization will still work.
        '''
        if node is not None:
            args = [repr(node.val)]
            if node.left:
                args += [f'left={repr_node_explicit(node.left)}']
            if node.right:
                args += [f'right={repr_node_explicit(node.right)}']
            return f'Node({",".join(args)})'

    def repr_node_min(node):
        ''' Same as above, except we try to avoid explicit keyword arg names when possible.
        '''
        if node is not None:
            args = [repr(node.val)]
            if node.left:
                args += [f'{repr_node_min(node.left)}']
                if node.right:
                    args += [f'{repr_node_min(node.right)}']
            elif node.right:
                args += [f'right={repr_node_min(node.right)}']
            return f'Node({",".join(args)})'
            
    modes = [
        repr_node_verbose,
        repr_node_explicit,
        repr_node_min,
    ]

    return modes[mode](node)


def deserialize(root_node_string, mode=0):

    modes = [
        eval,
        eval,
    ]
    return modes[mode](root_node_string)


if __name__ == '__main__':
    node = Node('root', Node('left', Node('left.left')), Node('right'))
    serialized_node = serialize(node, 2)
    print(serialize(node, 0))
    print(serialize(node, 1))
    print(serialize(node, 2))
    assert deserialize(serialized_node).left.left.val == 'left.left'