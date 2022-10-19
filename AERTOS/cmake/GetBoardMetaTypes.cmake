set(AESetupFiles)
set(AESetupFiles_PATHS)

if (${BOARD_USED} STREQUAL "STM32F411RE")
    set(BoardVendor STM32)
    set(BoardSeries F4)
    set(BoardModelType1 11)
    set(BoardModelType2 RE)

elseif (${BOARD_USED} STREQUAL "JetsonNano")
    set(BoardVendor Jetson)
    set(BoardSeries Nano)

elseif (${BOARD_USED} STREQUAL "RPI4B")
    set(BoardVendor RPI)
    set(BoardSeries 4)
    set(BoardModelType1 B)

    set(IsPC 1)

elseif (${BOARD_USED} STREQUAL "X64")
    set(IsPC 1)
else()
    message(FATAL_ERROR "Hadi: you chose a board that you never set in the GetBoardMetaTypes.cmake file")

endif ()






if (IsPC)

    set(directory ${CMAKE_SOURCE_DIR}/src/AE/AESetup/Board/Vendor_PC)
    if (NOT EXISTS ${directory})
        file(MAKE_DIRECTORY ${directory})
    endif ()

    #generate the BoardVendorSetup file
    set(file ${directory}/BoardVendorSetup.h)
    set(filecpp ${directory}/BoardVendorSetup.cpp)

    set(DERIVESFROM AESetUpBase)
    set(ForPart PC)

    Generate_File_Using_Cgen(
            WORKINGDIRECTORY ${directory}
            INPUT_FILE_NAME SetupFile
            OUTPUT_FILE_NAME BoardVendorSetup
            OUTPUT_FILE_EXTENSION h
    )
    Generate_File_Using_Cgen(
            WORKINGDIRECTORY ${directory}
            INPUT_FILE_NAME SetupFilecpp
            OUTPUT_FILE_NAME BoardVendorSetup
            OUTPUT_FILE_EXTENSION cpp
    )

    set(AESetupFiles ${AESetupFiles} ${file})
    set(AESetupFiles ${AESetupFiles} ${filecpp})
    set(AESetupFiles_PATHS ${AESetupFiles_PATHS} ${directory})


    add_compile_definitions(IsPC)
else()
    if (BoardVendor)

        #if there is no directory ${CMAKE_SOURCE_DIR}/src/AE/AESetup/BoardVendor_${BoardVendor}
        #create that directory if it exists
        set(directory ${CMAKE_SOURCE_DIR}/src/AE/AESetup/Board/Vendor_${BoardVendor})
        if (NOT EXISTS ${directory})
            file(MAKE_DIRECTORY ${directory})
        endif ()


        #generate the BoardVendorSetup file
        set(file ${directory}/BoardVendorSetup.h)
        set(filecpp ${directory}/BoardVendorSetup.cpp)

        set(DERIVESFROM AESetUpBase)
        set(ForPart ${BoardVendor})
        Generate_File_Using_Cgen(
                WORKINGDIRECTORY ${directory}
                INPUT_FILE_NAME SetupFile
                OUTPUT_FILE_NAME BoardVendorSetup
                OUTPUT_FILE_EXTENSION h
        )
        Generate_File_Using_Cgen(
                WORKINGDIRECTORY ${directory}
                INPUT_FILE_NAME SetupFilecpp
                OUTPUT_FILE_NAME BoardVendorSetup
                OUTPUT_FILE_EXTENSION cpp
        )

        set(AESetupFiles ${AESetupFiles} ${file})
        set(AESetupFiles ${AESetupFiles} ${filecpp})
        set(AESetupFiles_PATHS ${AESetupFiles_PATHS} ${directory})

        add_compile_definitions(BoardVendor=${BoardVendor})

    else()
        message(FATAL_ERROR "Hadi: if you are using a board, you at least need to specify the board's vendor type")
    endif()

    if (BoardSeries)

        #create that directory if it doesnt exists
        set(directory ${CMAKE_SOURCE_DIR}/src/AE/AESetup/Board/Vendor_${BoardVendor}/Series_${BoardSeries})
        if (NOT EXISTS ${directory})
            file(MAKE_DIRECTORY ${directory})
        endif ()


        #generate the BoardVendorSetup file
        set(file ${directory}/SeriesSetup.h)
        set(filecpp ${directory}/SeriesSetup.cpp)


        set(DERIVESFROM BoardVendorSetup)
        set(ForPart ${BoardSeries})
        Generate_File_Using_Cgen(
                WORKINGDIRECTORY ${directory}
                INPUT_FILE_NAME SetupFile
                OUTPUT_FILE_NAME SeriesSetup
                OUTPUT_FILE_EXTENSION h
        )
        Generate_File_Using_Cgen(
                WORKINGDIRECTORY ${directory}
                INPUT_FILE_NAME SetupFilecpp
                OUTPUT_FILE_NAME SeriesSetup
                OUTPUT_FILE_EXTENSION cpp
        )


        set(AESetupFiles ${AESetupFiles} ${file})
        set(AESetupFiles ${AESetupFiles} ${filecpp})
        set(AESetupFiles_PATHS ${AESetupFiles_PATHS} ${directory})

        add_compile_definitions(BoardSeries=${BoardSeries})
    endif ()


    if (BoardModelType1)

        #create that directory if it doesnt exists
        set(directory ${CMAKE_SOURCE_DIR}/src/AE/AESetup/Board/Vendor_${BoardVendor}/Series_${BoardSeries}/ModelType1_${BoardModelType1})
        if (NOT EXISTS ${directory})
            file(MAKE_DIRECTORY ${directory})
        endif ()


        #generate the BoardVendorSetup file
        set(file ${directory}/ModelType1Setup.h)
        set(filecpp ${directory}/ModelType1Setup.cpp)


        set(DERIVESFROM SeriesSetup)
        set(ForPart ${BoardModelType1})
        Generate_File_Using_Cgen(
                WORKINGDIRECTORY ${directory}
                INPUT_FILE_NAME SetupFile
                OUTPUT_FILE_NAME ModelType1Setup
                OUTPUT_FILE_EXTENSION h
        )
        Generate_File_Using_Cgen(
                WORKINGDIRECTORY ${directory}
                INPUT_FILE_NAME SetupFilecpp
                OUTPUT_FILE_NAME ModelType1Setup
                OUTPUT_FILE_EXTENSION cpp
        )


        set(AESetupFiles ${AESetupFiles} ${file})
        set(AESetupFiles ${AESetupFiles} ${filecpp})
        set(AESetupFiles_PATHS ${AESetupFiles_PATHS} ${directory})

        add_compile_definitions(BoardModelType1=${BoardModelType1})
    endif ()



    if (BoardModelType2)

        #create that directory if it doesnt exists
        set(directory ${CMAKE_SOURCE_DIR}/src/AE/AESetup/Board/Vendor_${BoardVendor}/Series_${BoardSeries}/ModelType1_${BoardModelType1}/ModelType2_${BoardModelType2})
        if (NOT EXISTS ${directory})
            file(MAKE_DIRECTORY ${directory})
        endif ()


        #generate the BoardVendorSetup file
        set(file ${directory}/ModelType2Setup.h)
        set(filecpp ${directory}/ModelType2Setup.cpp)


        set(DERIVESFROM ModelType1Setup)
        set(ForPart ${BoardModelType2})
        Generate_File_Using_Cgen(
                WORKINGDIRECTORY ${directory}
                INPUT_FILE_NAME SetupFile
                OUTPUT_FILE_NAME ModelType2Setup
                OUTPUT_FILE_EXTENSION h
        )
        Generate_File_Using_Cgen(
                WORKINGDIRECTORY ${directory}
                INPUT_FILE_NAME SetupFilecpp
                OUTPUT_FILE_NAME ModelType2Setup
                OUTPUT_FILE_EXTENSION cpp
        )

        set(AESetupFiles ${AESetupFiles} ${file})
        set(AESetupFiles ${AESetupFiles} ${filecpp})
        set(AESetupFiles_PATHS ${AESetupFiles_PATHS} ${directory})

        add_compile_definitions(BoardModelType2=${ModelType2})
    endif ()

endif ()
