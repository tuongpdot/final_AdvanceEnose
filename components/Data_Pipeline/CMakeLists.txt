set(SOURCES data_pipeline.cpp)
set(DEPENDS CPPI2C Sensor_Family)
idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS . 
                       REQUIRES ${DEPENDS})
