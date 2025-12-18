# Creating and displaying a directed graph for the Markov chain transition matrix P.
import matplotlib.pyplot as plt
import networkx as nx
import numpy as np

# Transition matrix P (4x4) from the problem
P = np.array([
    [0.23, 0.17, 0.33, 0.27],
    [0.21, 0.35, 0.23, 0.21],
    [0.18, 0.22, 0.28, 0.32],
    [0.19, 0.37, 0.09, 0.35]
])

# Create directed graph
G = nx.DiGraph()

# Add nodes (states 1..4)
num_states = P.shape[0]
nodes = list(range(1, num_states + 1))
G.add_nodes_from(nodes)

# Add edges with weights (probabilities)
for i in range(num_states):
    for j in range(num_states):
        prob = P[i, j]
        # Add edge even if probability is 0 (here none are 0), but skip extremely small values
        if prob > 0:
            G.add_edge(i+1, j+1, weight=prob)

# Position nodes in a circle for clarity
pos = nx.circular_layout(G)

# Draw nodes and labels
plt.figure(figsize=(6,6))
nx.draw_networkx_nodes(G, pos, node_size=900)
nx.draw_networkx_labels(G, pos, font_size=12, font_weight='bold')

# Draw directed edges
nx.draw_networkx_edges(G, pos, arrowstyle='->', arrowsize=18, connectionstyle='arc3,rad=0.15')

# Prepare edge labels (rounded to 2 decimal places)
edge_labels = {(u, v): f"{d['weight']:.2f}" for u, v, d in G.edges(data=True)}
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=10, label_pos=0.5)

plt.title("Đồ thị chuỗi Markov (các trạng thái 1..4)")
plt.axis('off')
plt.show()
