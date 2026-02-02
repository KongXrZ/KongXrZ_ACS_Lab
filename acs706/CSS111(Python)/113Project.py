import sys
import heapq

class Graph:
    def __init__(self, vertices):
        self.V = vertices  # จำนวนจุดยอด (N)
        # ใช้ Dictionary เก็บ Adjacency List: {node: [(neighbor, weight), ...]}
        self.graph = {i: [] for i in range(vertices)} 
        self.edges = [] # เก็บลิสต์ของ edges สำหรับ Kruskal: (weight, u, v)

    def add_edge(self, u, v, w):
        # กราฟแบบไม่มีทิศทาง (Undirected)
        self.graph[u].append((v, w))
        self.graph[v].append((u, w))
        self.edges.append((w, u, v))

    # 1. Spanning Tree ด้วย BFS
    def bfs_spanning_tree(self, start_node):
        visited = set()
        queue = [start_node]
        visited.add(start_node)
        spanning_edges = []

        while queue:
            u = queue.pop(0) # Dequeue
            for v, w in self.graph[u]:
                if v not in visited:
                    visited.add(v)
                    spanning_edges.append((u, v))
                    queue.append(v)
        return spanning_edges

    # 2. Dijkstra's Shortest Path
    def dijkstra(self, start_node, end_node):
        # ระยะทางเริ่มต้นเป็น Infinity
        distances = {i: float('inf') for i in range(self.V)}
        distances[start_node] = 0
        
        # Priority Queue เก็บ (distance, node)
        pq = [(0, start_node)]
        previous_nodes = {i: None for i in range(self.V)}

        while pq:
            current_dist, u = heapq.heappop(pq)

            if u == end_node:
                break # เจอปลายทางแล้วหยุด

            if current_dist > distances[u]:
                continue

            for v, weight in self.graph[u]:
                distance = current_dist + weight
                if distance < distances[v]:
                    distances[v] = distance
                    previous_nodes[v] = u
                    heapq.heappush(pq, (distance, v))

        # สร้างเส้นทางย้อนกลับ
        path = []
        curr = end_node
        if distances[end_node] == float('inf'):
            return "ไม่พบเส้นทาง", float('inf')
            
        while curr is not None:
            path.insert(0, curr)
            curr = previous_nodes[curr]
            
        return path, distances[end_node]

    # 3.1 Prim's Algorithm (Minimum Spanning Tree)
    def prim_mst(self):
        # เริ่มที่จุด 0 (หรือจุดใดก็ได้)
        start_node = 0
        visited = set([start_node])
        mst_edges = []
        total_weight = 0
        
        # Priority Queue เก็บ (weight, u, v) ของเส้นที่เชื่อมกับ visited set
        pq = []
        for v, w in self.graph[start_node]:
            heapq.heappush(pq, (w, start_node, v))

        while pq and len(visited) < self.V:
            w, u, v = heapq.heappop(pq)
            
            if v not in visited:
                visited.add(v)
                mst_edges.append((u, v, w))
                total_weight += w
                
                for next_v, next_w in self.graph[v]:
                    if next_v not in visited:
                        heapq.heappush(pq, (next_w, v, next_v))
                        
        return mst_edges, total_weight

    # 3.2 Kruskal's Algorithm (Minimum Spanning Tree)
    # Helper functions สำหรับ Union-Find
    def find_parent(self, parent, i):
        if parent[i] == i:
            return i
        return self.find_parent(parent, parent[i])

    def union(self, parent, rank, x, y):
        root_x = self.find_parent(parent, x)
        root_y = self.find_parent(parent, y)
        
        if rank[root_x] < rank[root_y]:
            parent[root_x] = root_y
        elif rank[root_x] > rank[root_y]:
            parent[root_y] = root_x
        else:
            parent[root_y] = root_x
            rank[root_x] += 1

    def kruskal_mst(self):
        mst_edges = []
        total_weight = 0
        
        # เรียงลำดับ edge ตามน้ำหนักจากน้อยไปมาก
        sorted_edges = sorted(self.edges, key=lambda item: item[0])
        
        parent = [i for i in range(self.V)]
        rank = [0] * self.V
        
        for w, u, v in sorted_edges:
            x = self.find_parent(parent, u)
            y = self.find_parent(parent, v)
            
            # ถ้าไม่เกิด cycle (ไม่อยู่ใน set เดียวกัน)
            if x != y:
                mst_edges.append((u, v, w))
                total_weight += w
                self.union(parent, rank, x, y)
                
        return mst_edges, total_weight

# --- การทดสอบ Code ---
# สร้างกราฟขนาด 5 จุด (0 ถึง 4)
g = Graph(5)
# เพิ่มเส้นเชื่อม (ต้นทาง, ปลายทาง, น้ำหนัก)
g.add_edge(0, 1, 2)
g.add_edge(0, 3, 6)
g.add_edge(1, 2, 3)
g.add_edge(1, 3, 8)
g.add_edge(1, 4, 5)
g.add_edge(2, 4, 7)
g.add_edge(3, 4, 9)

print("--- ผลลัพธ์แบบไม่ใช้ Library ---")
# 1. Spanning Tree (BFS)
print(f"1. BFS Spanning Tree (เริ่มที่ 0): {g.bfs_spanning_tree(0)}")

# 2. Dijkstra
path, dist = g.dijkstra(0, 4)
print(f"2. Dijkstra (0 -> 4): เส้นทาง {path}, ระยะรวม = {dist}")

# 3. MST (Prim & Kruskal)
prim_edges, prim_w = g.prim_mst()
print(f"3.1 Prim's MST: Edges {prim_edges}, Total Weight = {prim_w}")

kruskal_edges, kruskal_w = g.kruskal_mst()
print(f"3.2 Kruskal's MST: Edges {kruskal_edges}, Total Weight = {kruskal_w}")