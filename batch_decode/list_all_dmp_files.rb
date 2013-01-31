require 'rubygems'
require 'pdf/reader'


$output_file = "dmp_list.txt"

def list_dmp_in_dir(dir, hsh)
  new_dir = dir + "\\"
  begin
    Dir.foreach(new_dir){ |sub_dir|
      _dir = new_dir + sub_dir
      _dir = _dir.downcase

      if (File.directory?(_dir) && sub_dir != "." && sub_dir != "..")
        #puts _dir
        list_dmp_in_dir(_dir, hsh)
      elsif (File.extname(_dir) == ".dmp")
        if ( _dir.end_with?("_0.dmp") or _dir.end_with?("_1.dmp") )
          fnameprefix =  _dir[0...-6]
          
          hsh[fnameprefix] += 1
          
          #puts hsh[fnameprefix]
        end
      end
    }
  rescue Exception=>e
    	puts e
	end
end

def output_dmp_to_file(hsh)
  flog = File.open($output_file, "w")
    hsh.each { |fname, cnt|
      if cnt == 2
        #puts fname
        flog.puts fname
      end     
    }
  flog.close
end


def main(dir)
  dmp_hash = Hash.new(0)

  list_dmp_in_dir(dir.downcase, dmp_hash)

  output_dmp_to_file(dmp_hash)
end


###########################################

puts '======================================================'
if ARGV.count == 1
  puts "searching #{ARGV[0]} ..."
  if ARGV.count == 2
    $output_file = ARGV[1]
  end

  main(ARGV[0])
else
  puts 'give a directory name to search mimo-x2 dump files...'
end
puts '======================================================'



