require 'net/http'

# flst contains dump file names
def batch_decode_dmp(flst)
  t = Time.now

  system "mkdir batch_decode_results"

  output_dir = "batch_decode_results\\#{t.year}_#{t.mon}_#{t.day}__#{t.hour}_#{t.min}_#{t.sec}"

  system "mkdir #{output_dir}"

  puts output_dir

  hdmpfile = File.open(flst, 'r')

  hdmpfile.each_line{ |fname|
    fname = fname.chomp

    tmp = fname.reverse
    pos = tmp.index("\\")
    outname = fname[-pos...-1]
    puts fname

    cmd = "..\\release\\Cora.exe FileName1=#{fname}_0.dmp FileName2=#{fname}_1.dmp > #{output_dir}\\#{outname}.txt"
    #puts cmd
    system cmd
  }

  hdmpfile.close

end

#system "..\\release\\cora.exe"
#
#

puts '======================================================'
if ARGV.count == 1
  puts "batch decode #{ARGV[0]} ..."
  
  batch_decode_dmp(ARGV[0])
else
  puts 'give a dump file list to decode mimo-x2 dump files...'
end
puts '======================================================'

