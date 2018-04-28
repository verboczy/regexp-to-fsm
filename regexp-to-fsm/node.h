#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

class Node {
public:

    Node();
    Node(bool initial, bool fin);

    Node(Node const& other);
    Node& operator=(Node const& rhs);

    Node(Node && other);
    Node& operator=(Node && rhs);

    ~Node();

    void set_as_init();
    void set_as_final();

    bool get_is_init() const;
    bool get_is_final() const;

    bool operator< (Node const& rhs) const;

    int id;
private:
    static int max_id;
    //std::list<Edge> edges;
    bool is_init;
    bool is_final;
};

#endif
