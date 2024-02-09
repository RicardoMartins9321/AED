import random

def generate_dag(num_vertices, num_edges):
    edges = set()
    while len(edges) < num_edges:
        u = random.randint(0, num_vertices - 2)
        v = random.randint(u + 1, num_vertices - 1)
        edges.add((u, v))

    return edges

def save_to_file(filename, num_vertices, edges, is_digraph=1, is_weighted=0):
    with open(filename, 'w') as f:
        f.write(f"{is_digraph}\n{is_weighted}\n{num_vertices}\n{len(edges)}\n")
        for (u, v) in edges:
            f.write(f"{u} {v}\n")

num_vertices = 13  # example number of vertices
num_edges = 25    # example number of edges

edges = generate_dag(num_vertices, num_edges)
save_to_file("small_dag.txt", num_vertices, edges)
