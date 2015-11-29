{
  "build/fa" => 0,
  "build/fa -l" => 0,
  "build/fa --list" => 0,
  "build/fa github" => 0,
  "build/fa a" => 256,
}.each do |cmd, status|
  print "#{cmd} => "
  IO.pipe do |r, w|
    Process.waitpid(spawn(cmd, [:out, :err] => w))
    print $?.to_i
    if $?.to_i == status
      print " \e[32mok\e[m\n"
    else
      print " \e[32mfail\e[m\n"
    end
  end
end
