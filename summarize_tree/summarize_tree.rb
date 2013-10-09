#!/usr/bin/env ruby

dir = ARGV[0]
puts "Number of files:"
puts Dir[File.join(dir, '**', '*')].count { |file| File.file?(file) }
puts "Number of directories:"
puts (Dir["**/*"].length -  Dir[File.join(dir, '**', '*')].count { |file| File.file?(file) } + 1)
