cmake_minimum_required(VERSION 3.16)

project(financeManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Charts)

file(COPY data DESTINATION ${CMAKE_BINARY_DIR})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(financeManager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        dao/EntryDAO.cpp dao/EntryDAO.h data/expense.csv data/income.csv model/Entry.cpp model/Entry.h model/Expense.cpp model/Expense.h model/Income.cpp model/Income.h service/EntryService.cpp service/EntryService.h
        filter/AmountFilter.h filter/BaseFilter.h filter/DateFilter.h filter/Filter.h filter/NameFilter.h filter/TypeFilter.h
        filter/AmountFilter.cpp filter/AmountFilter.h filter/BaseFilter.cpp filter/BaseFilter.h filter/DateFilter.cpp filter/DateFilter.h filter/Filter.h filter/NameFilter.cpp filter/NameFilter.h filter/TypeFilter.cpp filter/TypeFilter.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET financeManager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(financeManager SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(financeManager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(financeManager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.financeManager)
endif()
set_target_properties(financeManager PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS financeManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}

)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(financeManager)
endif()
