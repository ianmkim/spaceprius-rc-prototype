class Graph:
    def __init__(self, graph_dict=None, directed=True):
        self.graph_dict = graph_dict or {}
        self.directed = directed

        if not directed:
            self.make_undirected()

    def make_undirected(self):
        for a in list(self.graph_dict.keys()):
            for (b, dist) in self.graph_dict[a].items():
                self.graph_dict.setdefault(b, {}) [a] = dist

    def connect(self, A, B, distance=1):
        self.graph_dict.setdefault(A, {})[B] = distance
        if not self.directed:
            self.graph_dict.setdefault(B, {})[A] = distance

    def get(self, a, b=None):
        links = self.graph_dict.setdefault(a, {})
        if b is None:
            return links
        else:
            return links.get(b)

    def nodes(self):
        s1 = set([k for k in self.graph_dict.keys()])
        s2 = set([k2 for v in self.graph_dict.values() for k2, v2 in v.items()])

        nodes = s1.union(s2)
        return list(nodes)

class Node:
    def __init__(self, name:str, parent:str):
        self.name = name
        self.parent = parent
        self.g = 0
        self.h = 0
        self.f = 0

    def __eq__(self, other):
        return self.name == other.name

    def __lt__(self, other):
        return self.f < other.f

    def __repr__(self):
        return ('({0}, {1})'.format(self.name, self.f))

def astar_search(graph, heuristics, start, end):
    open = []
    closed = []
    start_node = Node(start, None)
    goal_node = Node(end, None)

    open.append(start_node)

    while len(open) > 0:
        open.sort()
        print(len(open))
        current_node = open.pop(0)
        closed.append(current_node)

        if current_node == goal_node:
            path = []
            while current_node != start_node:
                path.append(current_node.name + ": " + str(current_node.g))
                current_node = current_node.parent
            path.append(start_node.name + ": " + str(start_node.g))

            return path[::-1]

        neighbors = graph.get(current_node.name)
        print(closed)

        for key, value in neighbors.items():
            neighbor = Node(key, current_node)

            if neighbor in closed:
                continue
            neighbor.g = current_node.g + graph.get(current_node.name, neighbor.name)
            neighbor.h = heuristics.get(neighbor.name)
            neighbor.f = neighbor.g + neighbor.h

            if(add_to_open(open, neighbor) == True):
                open.append(neighbor)


    return None

def add_to_open(open, neighbor):
    for node in open:
        if(neighbor == node and neighbor.f > node.f):
            return False
    return True

def main():
    graph = Graph()
        # Create graph connections (Actual distance)
    graph.connect('1', '2', 111)
    graph.connect('1', '3', 85)
    graph.connect('2', '4', 104)
    graph.connect('2', '5', 140)
    graph.connect('2', '6', 183)
    graph.connect('3', '4', 230)
    graph.connect('3', '7', 67)
    graph.connect('7', '8', 191)
    graph.connect('7', '5', 64)
    graph.connect('4', '6', 171)
    graph.connect('4', '9', 170)
    graph.connect('4', '10', 220)
    graph.connect('5', '6', 107)
    graph.connect('8', '11', 91)
    graph.connect('8', '12', 85)
    graph.connect('11', '12', 120)
    graph.connect('12', '13', 184)
    graph.connect('13', '6', 55)
    graph.connect('13', '9', 115)
    graph.connect('9', '6', 123)
    graph.connect('9', '10', 189)
    graph.connect('9', '14', 59)
    graph.connect('14', '15', 81)
    graph.connect('10', '16', 102)
    graph.connect('15', '16', 126)
    # Make graph undirected, create symmetric connections
    graph.make_undirected()
    # Create heuristics (straight-line distance, air-travel distance)
    heuristics = {}
    heuristics['8'] = 204
    heuristics['11'] = 247
    heuristics['1'] = 215
    heuristics['7'] = 137
    heuristics['16'] = 318
    heuristics['3'] = 164
    heuristics['9'] = 120
    heuristics['13'] = 47
    heuristics['4'] = 132
    heuristics['10'] = 257
    heuristics['14'] = 168
    heuristics['5'] = 75
    heuristics['15'] = 236
    heuristics['2'] = 153
    heuristics['12'] = 157
    heuristics['6'] = 0
    # Run the search algorithm
    path = astar_search(graph, heuristics, '1', '6')
    print(path)
    print()

if __name__ == "__main__": main()
