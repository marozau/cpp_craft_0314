Function DeleteTextData
{
    del C:\Users\I.Kolupaev\Documents\CppCraft\cpp_craft_0314\solutions\igor_kolupaev\3\_build_Debug_64\bin_64\Debug\*.txt
}

Function CreateInputFiles
{
    param( $source, $start, $finish )

    for($i = $start; $i -le $finish; $i++){
        $s = $i.ToString().PadLeft(3,'0')
        copy $source input_$s.txt
    }
}

Function TestOutputSize
{
    param( $start, $finish, $size )

    $errors_count = 0;

    for($i = $start; $i -le $finish; $i++)
    {
        $s = $i.ToString().PadLeft(3,'0')
        $filename = "output_$s.txt"

        if( (Get-Item $filename).Length -ne $size )
        {
            Write-Error -Message "$filename test failed"
            $errors_count++;
        }
    }

    return $errors_count
} 

cd C:\Users\I.Kolupaev\Documents\CppCraft\cpp_craft_0314\solutions\igor_kolupaev\3\_build_Debug_64\bin_64\Debug

DeleteTextData

CreateInputFiles C:\Users\I.Kolupaev\Documents\CppCraft\cpp_craft_0314\solutions\igor_kolupaev\2\_build_Debug_64\bin_64\Debug\input_241.txt 1 900
CreateInputFiles C:\Users\I.Kolupaev\Documents\CppCraft\cpp_craft_0314\solutions\igor_kolupaev\2\_build_Debug_64\bin_64\Debug\input_242.txt 901 950
CreateInputFiles C:\Users\I.Kolupaev\Documents\CppCraft\cpp_craft_0314\solutions\igor_kolupaev\2\_build_Debug_64\bin_64\Debug\input_243.txt 951 999

3_4

$errors_count = 0;
$errors_count += TestOutputSize( 1, 900, 192 )
$errors_count += TestOutputSize( 901, 951, 2400000 )
$errors_count += TestOutputSize( 951, 999, 6400000 )

Write-Output "3_4 is done with $errors_count errors"

DeleteTextData

CreateInputFiles C:\Users\I.Kolupaev\Documents\CppCraft\cpp_craft_0314\solutions\igor_kolupaev\2\_build_Debug_64\bin_64\Debug\input_251.txt 1 800
CreateInputFiles C:\Users\I.Kolupaev\Documents\CppCraft\cpp_craft_0314\solutions\igor_kolupaev\2\_build_Debug_64\bin_64\Debug\input_252.txt 801 900
CreateInputFiles C:\Users\I.Kolupaev\Documents\CppCraft\cpp_craft_0314\solutions\igor_kolupaev\2\_build_Debug_64\bin_64\Debug\input_253.txt 901 999

3_5

$errors_count = 0;
$errors_count += TestOutputSize( 1, 800, 60)
$errors_count += TestOutputSize( 801, 900, 0 )
$errors_count += TestOutputSize( 901, 999, 24 )

Write-Output "3_5 is done with $errors_count errors"

DeleteTextData