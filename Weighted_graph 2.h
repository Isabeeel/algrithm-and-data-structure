#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include <queue>
#include "Exception.h"

/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

class Weighted_graph {
	private:
		static const double INF;
		// your choice
        double **graph_matrix=nullptr;
        int edge_num,vertex;
    
    
	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double minimum_spanning_tree( int ) const;
		bool is_connected() const;

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator << ( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Enter definitions for all public functions here

Weighted_graph::Weighted_graph(int n){
    if (n<0) throw illegal_argument();
    //define n*n
    vertex=n;
    edge_num=0;
    graph_matrix = (double **)malloc(sizeof(double *) * n);
    for(int i=0; i<n; i++)
    {
        graph_matrix[i] = (double *)malloc(sizeof(double) * (n));
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (i==j) graph_matrix[i][j]=0;
            else graph_matrix[i][j]=INF;
        }
    }
}
Weighted_graph::~Weighted_graph(){
//    delete[] graph_matrix;
    //vertex=0;
}

int Weighted_graph::degree(int n) const {
    if (n<0 || n>=vertex) {
        throw illegal_argument();
    }
    int n_adj=0;
    for (int i=0; i<vertex; i++) {
        if (graph_matrix[n][i]!=INF && graph_matrix[n][i]!=0 ) {
            n_adj++;
        }
    }
    return n_adj;
}

int Weighted_graph::edge_count() const{
    return edge_num;
}

double Weighted_graph::adjacent( int m, int n ) const{
    if (n<0 || n>=vertex||m<0||m>=vertex) {
        throw illegal_argument();
    }
    return graph_matrix[m][n];
}

double Weighted_graph::minimum_spanning_tree( int m) const{
    if (m<0||m>=vertex) {
        throw illegal_argument();
    }
    double lowcast[vertex];
    int visited[vertex];
    double total_weight;
    total_weight=0;
    double minn=INF;
    int minid=m;
    for (int i=0; i<vertex; i++) {
        visited[i]=0;
        lowcast[i]=INF;
    }
    visited[m]=1;
    for (int i=0; i<vertex; i++) {
        lowcast[i]=graph_matrix[m][i];
        //std::cout<<lowcast[i]<<std::endl;
        if (lowcast[i]<minn && lowcast[i]!=0) {
            minn=lowcast[i];
            minid=i;
        }
    }
    if (lowcast[minid]!=0) {
        visited[minid]=1;
        total_weight+=lowcast[minid];
        //std::cout<<"total weight"<<total_weight<<std::endl;
    }
    for (int h=1; h<vertex; h++) {
        minn=INF;
        for (int s=0; s<vertex; s++) {
            if (lowcast[s]>graph_matrix[minid][s]&&lowcast[s]>0 && visited[s]==0) {
                lowcast[s]=graph_matrix[minid][s];
            }
            //std::cout<<lowcast[s]<<std::endl;
            //std::cout<<"==========="<<std::endl;
        }
        for (int s=0; s<vertex; s++) {
            if (lowcast[s]<minn&&lowcast[s]>0 && visited[s]==0) {
                minn=lowcast[s];
                minid=s;
            }
        }
        if (minn==INF) {
            return total_weight;
        }
        if (lowcast[minid]!=0) {
            visited[minid]=1;
            total_weight+=lowcast[minid];
            //std::cout<<"total weight"<<total_weight<<std::endl;
        }
        //total_weight+=lowcast[minid];
        //lowcast[minid]=0;
        //visited[minid]=1;
    }
    return total_weight;
}

bool Weighted_graph::is_connected() const{
    int count=1;
    int visited[vertex];
    std::queue<int> graphVertex;
    graphVertex.push(0);
    for (int i=0; i<vertex; i++) {
        visited[i]=0;
    }
    visited[0]=1;
    while (!graphVertex.empty()) {
        int tp=graphVertex.front();
        visited[tp]=1;
        graphVertex.pop();
        for (int j=0; j<vertex; j++) {
            if (graph_matrix[tp][j]!=INF&&visited[j]==0) {
                visited[j]=1;
                graphVertex.push(j);
                count++;
            }
        }
    }
    if (count==vertex) {
        return true;
    }
    //int i_i=0;
    //while (i_i<vertex && visited[i_i]==1) {
    //    i_i++;
    //    if (i_i==vertex) {
    //        return true;
    //    }
    //}
    return false;
}

void Weighted_graph::insert( int m, int n, double w){
    if (n<0 || n>=vertex||m<0||m>=vertex||w<0||w==INF||m==n) {
        throw illegal_argument();
    }
    if (graph_matrix[m][n]==INF) {
        if (w==0) {
            return;
        }else{
            graph_matrix[m][n]=w;
            graph_matrix[n][m]=w;
            edge_num++;
        }
    }else{
        if (w==0) {
            graph_matrix[m][n]=INF;
            graph_matrix[n][m]=INF;
            edge_num--;
            return;
        }
        graph_matrix[m][n]=w;
        graph_matrix[n][m]=w;
        //std::cout<<"insert"<<graph_matrix[m][n]<<std::endl;
        //edge_num++;
    }
    return;
}
std::ostream &operator << ( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation
	return out;
}



#endif
