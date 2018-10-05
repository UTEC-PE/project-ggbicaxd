#ifndef NODE_H
#define NODE_H

template <typename G>
class Node {
    public:
        typedef typename G::N N;
        typedef typename G::E E;
        typedef typename G::edge edge;
        typedef typename G::EdgeSeq EdgeSeq;

        EdgeSeq edges;
        Node(N data, double x, double y)
        {
            this->data = data;
            this->x = x;
            this->y = y;
        }
        

    private:
        N data;
        double x;
        double y;

};

#endif