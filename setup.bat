cd build
cmake -G "MinGW Makefiles" ..

if exist compile_commands.json (
    if exist ..\compile_commands.json (
        del ..\compile_commands.json
    )
    move compile_commands.json ..
)