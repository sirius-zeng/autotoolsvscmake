add_library(pricetable PriceTable.cc)

# Include direcotry for specific target.
target_include_directories(pricetable PUBLIC ${PROJECT_BINARY_DIR})