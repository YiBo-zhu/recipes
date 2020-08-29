/*************************************************************************
    > File Name: TaskAnalyzer.hpp
    > Author: Netcan
    > Descripton: TaskAnalyzer
    > Blog: https://netcan.github.io/
    > Mail: 1469709759@qq.com
    > Created Time: 2020-08-29 18:27
************************************************************************/
#pragma once
#include "Typelist.hpp"
template<typename ...Links>
class TaskAnalyzer {
    template<typename FROMs, typename TOs, typename = void>
    struct BuildOneToOneLink;

    template<typename ...Fs, typename Ts>
    struct BuildOneToOneLink<TypeList<Fs...>, Ts> {
        using type = Concat_t<typename BuildOneToOneLink<Fs, Ts>::type...>;
    };

    template<typename F, typename... Ts>
    struct BuildOneToOneLink<F, TypeList<Ts...>, std::enable_if_t<!IsTypeList_v<F>>> {
        using type = TypeList<OneToOneLink<F, Ts>...>;
    };

    template<typename Link>
    class OneToOneLinkSetF {
        using FromJobList = typename Link::FromJobList;
        using ToJobList = typename Link::ToJobList;
    public:
        using type = typename BuildOneToOneLink<FromJobList, ToJobList>::type;
    };

public:
    using AllJobs = Unique_t<Concat_t<typename Connection<Links>::FromJobList..., typename Connection<Links>::ToJobList...>>;
    using OneToOneLinkSet = Unique_t<Flatten_t<Map_t<TypeList<Connection<Links>...>, OneToOneLinkSetF>>>;
};
