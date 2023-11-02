
void DEBUG() {
    std::cerr << "Unsuccesfull Console Valuable;";
}

template<class T, class ...U> void DEBUG(T a, U ...b) {
    std::cerr << a;
    if(sizeof...(b)) {
        std::cerr << " | ";
        DEBUG(b...);
    }
}

#define console(...) \
    std::cerr << "Line " << __LINE__ << "| "<<  #__VA_ARGS__ << ": ", DEBUG(__VA_ARGS__), std::cerr << '\n'


template<class T1, class T2> 
std::ostream& operator << (std::ostream& cout, std::pair<T1, T2> Q) {
    cout << "[" << Q.first << ", " << Q.second << "]";
    return cout;
}

template<class Con, class = decltype(std::declval<Con>().begin())>
typename std::enable_if<!std::is_same<Con, std::string>::value, std::ostream&>::type
operator << (std::ostream& cout, Con Q) {
    cout << "[SIZE = " << Q.size() << "]: {";
    for(auto It = Q.begin(); It != Q.end(); ++It) 
        cout << (It == Q.begin() ? "" : ", ") << *It; 
    cout << "}";
    return cout;
}

template<class Con, class T = decltype(std::declval<Con>().top())> 
T Pick(Con u) { return u.top(); }
template<class T> 
T Pick(std::queue<T> u) { return u.front(); }

template<class Con, class = decltype(Pick(std::declval<Con>()))>
std::ostream& operator << (std::ostream& cout, Con Q) {
    cout << "[SIZE = " << Q.size() << "]: {";
    if(Q.size())
    for(cout << Pick(Q), Q.pop(); Q.size(); Q.pop())
        cout << ", " << Pick(Q);
    cout << "}";
    return cout;
}