#include <iostream>
#include <vector>
#include <numeric>
#include <tipe/tipe.hpp>
#include <type_traits>

struct iota
{
    std::vector<int>
    operator()(int x) const
    {
        std::vector<int> ret(x);
        std::iota(ret.begin(), ret.end(), 1);
        return ret;
    }
};

static auto get_graph()
{
    auto nodes = tip::make_nodes(
        tip::nodes::constant<1>{},
        [](int x) { return x * 2; },
        tip::nodes::print{ std::cout, "\n" }
    );

    auto ids = tip::get_ids(nodes);
    auto& [entry, mul, print] = ids;

    auto edges = make_edges(ids)
        .connect(entry | mul | print)
        .connect(entry | print);

    return make_graph(std::move(nodes), edges);
}

int main()
{
    auto foo = get_graph();
    tip::execute(foo, tip::node_id_t<1>{});
}