#include "Mesh.h"

Mesh::Mesh(const char* filename)
{
	int nVerts, nTris, n, k = 0;
	double x, y, z;
	minHeap.push_back(0);

	ifstream file(filename);

	string line;
	getline(file, line);
	getline(file, line);
	stringstream str(line);
	str >> nVerts >> nTris >> n;

	while (k++ < nVerts)
	{
		getline(file, line);
		stringstream str2(line);

		str2 >> x >> y >> z;
		addVertex(x, y, z); // Not Implemented.
	}
	k = 0;
	while (k++ < nTris)
	{
		getline(file, line);
		stringstream str2(line);

		str2 >> n >> x >> y >> z;
		addTriangle((size_t)x, (size_t)y, (size_t)z); // Not Implemented.
	}

	file.close();

	buildHeap(); // Not Implemented.
}


size_t Mesh::addVertex(double x, double y, double z) {
    size_t index=verts.size();
    verts.push_back(Vertex(index,x,y,z));
	return index;
}
size_t Mesh::addTriangle(size_t v1, size_t v2, size_t v3) {
    size_t index=tris.size();
    tris.push_back(Triangle(index,v1,v2,v3));
    
    verts[v1].triList.push_back(index);//add new triangle index to vertexes triList
    verts[v2].triList.push_back(index);
    verts[v3].triList.push_back(index);
    
    addEdge(v1,v2);
    addEdge(v2,v3);
    addEdge(v1,v3);
    
    return index;
}

void Mesh::addEdge(size_t v1, size_t v2) {
    if(isVertsNeighbour(v1,v2))return;
    
    size_t index=edges.size();
    Edge e= Edge(index,v1,v2);
    e.length=dist(verts[v1].coords,verts[v2].coords);
    edges.push_back(e);
    
    minHeap.push_back(index);
    
    verts[v1].edgeList.push_back(index);
    verts[v2].edgeList.push_back(index);
    
    verts[v1].vertList.push_back(v2);
    verts[v2].vertList.push_back(v1);
    
    
    
	
}

void Mesh::bubbleDown(int hole){
    size_t temp=minHeap[hole];
    
    int child, size=minHeap.size()-1;
    while(hole*2<=size){
        child= 2*hole;
        if (child != size && edges[minHeap[child + 1]].length < edges[minHeap[child]].length) {
            child++;
        }
        
        if (edges[minHeap[child]].length < edges[temp].length) {
            minHeap[hole] = minHeap[child];
            hole=child;
        } else {
            break;
        }
        
    }
    minHeap[hole] = temp;
    
}


void Mesh::buildHeap() {
   size_t last=minHeap.size()-1;
   for(size_t i=last/2;i>0;i--){
       bubbleDown(i);
   }
}

Edge& Mesh::getEdge(size_t v1, size_t v2) {
    for(size_t i=0;i<verts[v1].edgeList.size();i++){
        size_t edgeIndex=verts[v1].edgeList[i];
        if(edges[edgeIndex].v1i==v2||edges[edgeIndex].v2i==v2)return edges[edgeIndex];
    }
    return edges[0];
}

void Mesh::printVertex(size_t v) {
    if(v<verts.size()){
        
        cout<< verts[v].coords[0] <<" "<< verts[v].coords[1]<<" "<< verts[v].coords[2] <<" ";
    }
}

void Mesh::printTriangle(size_t t) {
    if(t<tris.size()){
        
        cout<< 3<<" " <<tris[t].v1i<< " "<<tris[t].v2i<<" "<<tris[t].v3i<<" ";
    }
}

bool Mesh::isVertsNeighbour(size_t v1, size_t v2) {
    for(size_t i=0;i<verts[v1].vertList.size();i++){
        size_t vertIndex=verts[v1].vertList[i];
        if(vertIndex==v2)return true;//vertındexle kıyaslaman yeterli ikisi de index
    }
    return false;
}

size_t Mesh::getDegree(size_t v) {
    if(v>=verts.size()){
        return 0;
    }
	return verts[v].vertList.size();
}

int Mesh::getJumpCount(size_t v1, size_t v2)
{
    if(v1==v2)return 0;
    
    vector<size_t> distances(verts.size(),-1);
    std::queue<size_t> q; //
    
    q.push(v1);
    distances[v1]=0;
    
    while(!q.empty()){
        size_t u=q.front();
        q.pop();
        
        if(u==v2)return distances[u];
        
        for(size_t i=0;i<verts[u].vertList.size();i++){
            size_t v=verts[u].vertList[i];
            if(distances[v]==-1){
                distances[v]=distances[u]+1;
                q.push(v);
            }
        }
    }
    return -1;
}




double Mesh::getGeodesicDistance(size_t v1, size_t v2) {
   size_t n = verts.size();
    
    // 1. DBL_MAX: Sonsuz yerine kullanılabilecek en büyük double değer
    vector<double> dist(n, DBL_MAX);
    vector<bool> visited(n, false);
    
    dist[v1] = 0;

    for(size_t i = 0; i < n; i++) {
        
        // --- En yakın ziyaret edilmemiş düğümü bulma ---
        int u = -1;
        for(size_t j = 0; j < n; j++) {
            if(!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        // Eğer gidilecek yol kalmadıysa veya en yakın yer sonsuz uzaklıktaysa dur
        if(u == -1 || dist[u] == DBL_MAX) 
            break;

        // Hedefe vardıysak sonucu döndür (Erken Çıkış)
        if(u == v2) return dist[u];

        visited[u] = true;

        // --- 2. Klasik FOR Döngüsü ---
        // Range-based for (auto x : list) yerine klasik indeksli yapı:
        for(size_t k = 0; k < verts[u].vertList.size(); k++) {
            
            size_t neighbor = verts[u].vertList[k]; // Komşuyu indeksten al

            // Eğer komşu zaten ziyaret edildiyse atla (Opsiyonel hızlandırma)
            if(visited[neighbor]) continue;

            // Kenar uzunluğunu al
            double weight = getEdge(u, neighbor).length; 

            // Mesafe güncelleme (Relaxation)
            if(dist[u] + weight < dist[neighbor]) {
                dist[neighbor] = dist[u] + weight;
            }
        }
    }

    return dist[v2];
    
    
}

void Mesh::updateVertex(size_t v, double x, double y, double z) {
    Vertex& v1= verts[v];
    v1.coords[0]=x;
    v1.coords[1]=y;
    v1.coords[2]=z;
    
    for(size_t i=0;i<v1.edgeList.size();i++){
        Edge& e=edges[v1.edgeList[i]];
        size_t v2i=(v==e.v1i)? e.v2i:e.v1i;
        Vertex& v2=verts[v2i];
        e.length=dist(v1.coords,v2.coords);
    }
    buildHeap();
    
    
    
    
}


void Mesh::removeMin(){
    if(minHeap.size()==1) return ;
    if(minHeap.size()==2) {
        minHeap.pop_back();
        return ;
    }
    size_t last=minHeap[minHeap.size()-1];
    minHeap[1]=last;
    minHeap.pop_back();
    bubbleDown(1);
}

void Mesh::add(size_t &x){
    minHeap[0]=x;
    minHeap.push_back(x);
    int hole=minHeap.size()-1;
    while( edges[x].length<edges[minHeap[hole/2]].length) {
        minHeap[hole]=minHeap[hole/2];
        hole=hole/2;
}
    minHeap[hole]=x;
    
}

Edge& Mesh::getKthShortestEdge(size_t k) {
    if(k>=minHeap.size()) return edges[0];

	vector<size_t> vec;
	for(int i=0;i<=k;i++){
	    vec.push_back(minHeap[1]);
	    removeMin();
	}


	for(int i=vec.size()-1;i>=0;i--){
	    add(vec[i]);
    
	}

	return edges[vec[vec.size()-1]];
}

// Implement your helper functions here.