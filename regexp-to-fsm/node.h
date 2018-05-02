#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

class Node {
public:

    Node();
    Node(bool initial, bool fin);

    void set_as_final();

    bool get_is_init() const;
    bool get_is_final() const;

    bool operator< (Node const& rhs) const;

private:
    int id;
    static int max_id;

    bool is_init;
    bool is_final;
};

#endif
