set(SOURCES Base_.cpp Temp_sen.cpp C02_sen.cpp)

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS ./include
                       REQUIRES Data_Pipeline)
