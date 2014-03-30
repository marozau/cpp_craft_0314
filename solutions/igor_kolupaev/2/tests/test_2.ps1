cd C:\Users\I.Kolupaev\Documents\CppCraft\cpp_craft_0314\solutions\igor_kolupaev\2\_build_Debug_64\bin_64\Debug

copy input_241.txt input.txt
2_4
if( (Get-Item output.txt).Length -ne 192 )
{
    Write-Error -Message "input_241.txt test failed"
}
else
{
    Write-Output "input_241.txt test OK"
}

copy input_242.txt input.txt
2_4
if( (Get-Item output.txt).Length -ne 2400000 )
{
    Write-Error -Message "input_242.txt test failed"
}
else
{
    Write-Output "input_242.txt test OK"
}

copy input_243.txt input.txt
2_4
if( (Get-Item output.txt).Length -ne 6400000 )
{
    Write-Error -Message "input_243.txt test failed"
}
else
{
    Write-Output "input_243.txt test OK"
}

copy input_251.txt input.txt
2_5
if( (Get-Item output.txt).Length -ne 60 )
{
    Write-Error -Message "input_251.txt test failed"
}
else
{
    Write-Output "input_251.txt test OK"
}

copy input_252.txt input.txt
2_5
if( (Get-Item output.txt).Length -ne 0 )
{
    Write-Error -Message "input_252.txt test failed"
}
else
{
    Write-Output "input_252.txt test OK"
}

copy input_253.txt input.txt
2_5
if( (Get-Item output.txt).Length -ne 24 )
{
    Write-Error -Message "input_253.txt test failed"
}
else
{
    Write-Output "input_253.txt test OK"
}

copy input_261.txt input.txt
2_6
if( (Get-Item output.txt).Length -ne 231 )
{
    Write-Error -Message "input_261.txt test failed"
}

$o = Get-Content output.txt
$o1 = Get-Content output_261.txt
$diff = Compare-Object $o $o1

if( $diff.Length -ne 0 )
{
    Write-Error -Message "output_261 content doesn't match"
}
else
{
    Write-Output "input_261.txt test OK"
}

copy input_262.txt input.txt
2_6
if( (Get-Item output.txt).Length -ne 66000000 )
{
    Write-Error -Message "input_262.txt test failed"
}

$o = Get-Content output.txt
$o1 = Get-Content output_262.txt
$diff = Compare-Object $o $o1

if( $diff.Length -ne 0 )
{
    Write-Error -Message "output_261 content doesn't match"
}
else
{
    Write-Output "input_262.txt test OK"
}
