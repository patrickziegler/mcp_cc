set(COVERAGE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/coverage")
set(BASELINE "${COVERAGE_OUTPUT_DIR}/baseline.info")
set(TRACEFILE "${COVERAGE_OUTPUT_DIR}/trace.info")
set(REPORT_DIR "${COVERAGE_OUTPUT_DIR}/report")

add_custom_command(
    OUTPUT "${TRACEFILE}" always
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${COVERAGE_OUTPUT_DIR}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${COVERAGE_OUTPUT_DIR}"

    COMMAND lcov
                --zerocounters
                --directory "${CMAKE_BINARY_DIR}"

    COMMAND lcov
                --capture
                --initial
                --directory "${CMAKE_BINARY_DIR}"
                --output-file "${BASELINE}"

    COMMAND ${CMAKE_CTEST_COMMAND} # executing the test suite

    COMMAND lcov
                --capture
                --directory "${CMAKE_BINARY_DIR}"
                --output-file "${TRACEFILE}"

    COMMAND lcov
                --add-tracefile "${BASELINE}"
                --add-tracefile "${TRACEFILE}"
                --output-file "${TRACEFILE}"

    COMMAND lcov
                --extract ${TRACEFILE}
                    "${CMAKE_SOURCE_DIR}/*"
                --output-file ${TRACEFILE}

    COMMAND lcov
                --remove ${TRACEFILE}
                    "${CMAKE_SOURCE_DIR}/build/*"
                    "${CMAKE_SOURCE_DIR}/extern/*"
                    "${CMAKE_SOURCE_DIR}/app/main.cpp"
                    "${CMAKE_SOURCE_DIR}/app/test/*"
                    "${CMAKE_SOURCE_DIR}/lib/test/*"
                --output-file ${TRACEFILE}

    COMMAND genhtml ${TRACEFILE}
                --output-directory ${REPORT_DIR}

    VERBATIM # for correct handling of wildcards in command line parameters
)

add_custom_target(coverage
    DEPENDS ${TRACEFILE} always)
