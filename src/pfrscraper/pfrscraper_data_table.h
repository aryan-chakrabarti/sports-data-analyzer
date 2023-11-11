#ifndef INCLUDE_PFR_SCRAPER_DATA_TABLE
#define INCLUDE_PFR_SCRAPER_DATA_TABLE

#include <map>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace pfrscraper {

template <class T>
class DataTable {
    typedef std::vector<std::pair<std::string, T>> Row;
    typedef std::vector<T*> Column;
    typedef std::shared_ptr<Row> RowPtr;
    // 2D vector of shared pointer to a vector of (id, value) pairs.
    typedef std::vector<RowPtr> Table;

    Table m_table;
    std::map<std::string, Row*> m_rowMap;
    std::map<std::string, Column> m_colMap;
    std::string m_name;

   public:
    inline DataTable(const std::string& name = "") : m_name(name) {}
    inline void add(const std::string& rowName, const Row& dataRow) {
        bool initiallyEmpty(m_table.empty());
        RowPtr row(std::make_shared<Row>(dataRow));
        m_table.emplace_back(row);
        m_rowMap.emplace(std::pair<std::string, Row*>(rowName, row.get()));
        for (std::pair<std::string, T>& dataTuple : *row) {
            if (!initiallyEmpty &&
                m_colMap.find(dataTuple.first) == m_colMap.end()) {
                throw std::out_of_range("Column name " + dataTuple.first +
                                        " not found in table for row " +
                                        rowName);
            }
            if (initiallyEmpty) {
                m_colMap.emplace(std::pair<std::string, std::vector<T*>>(
                    dataTuple.first, std::vector<T*>()));
            }
            m_colMap.at(dataTuple.first).emplace_back(&dataTuple.second);
        }
    }

    std::string name() const { return m_name; }

    void setName(const std::string& name) { m_name = name; }

    std::map<std::string, Column> columns() const { return m_colMap; }

    std::map<std::string, Row*> rows() const { return m_rowMap; }

    Table table() const { return m_table; }
};

template <class T>
class DataTableMap {
    std::unordered_map<std::string, DataTable<T>> m_tableMap;

   public:
    inline std::unordered_map<std::string, DataTable<T>>& map() {
        return m_tableMap;
    }
};

}  // namespace pfrscraper

#endif