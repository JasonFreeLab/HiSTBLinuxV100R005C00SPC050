#!/usr/bin/env python
#coding:utf-8
#----------------------------------------------------------------------------
# tools for generate a trusted application load image
#----------------------------------------------------------------------------

import os
import sys
import time
import traceback
import struct
import hashlib
import string
import ConfigParser
import uuid
import binascii

# ELF Definitions
ELF_HDR_SIZE              = 52
ELF_PHDR_SIZE             = 32
ELFINFO_MAG0_INDEX        = 0
ELFINFO_MAG1_INDEX        = 1
ELFINFO_MAG2_INDEX        = 2
ELFINFO_MAG3_INDEX        = 3
ELFINFO_MAG0              = '\x7f'
ELFINFO_MAG1              = 'E'
ELFINFO_MAG2              = 'L'
ELFINFO_MAG3              = 'F'
ELFINFO_CLASS_INDEX       = 4
ELFINFO_CLASS_32          = '\x01'
ELFINFO_VERSION_INDEX     = 6
ELFINFO_VERSION_CURRENT   = '\x01'
ELF_BLOCK_ALIGN           = 0x1000

# ELF Program Header Types
NULL_TYPE                 = 0x0
LOAD_TYPE                 = 0x1
DYNAMIC_TYPE              = 0x2
INTERP_TYPE               = 0x3
NOTE_TYPE                 = 0x4
SHLIB_TYPE                = 0x5
PHDR_TYPE                 = 0x6
TLS_TYPE                  = 0x7

#----------------------------------------------------------------------------
# Verify ELF header contents from an input ELF file
#----------------------------------------------------------------------------
def verify_elf_header(elf_header):
   if (elf_header.e_ident[ELFINFO_MAG0_INDEX] != ELFINFO_MAG0) or \
      (elf_header.e_ident[ELFINFO_MAG1_INDEX] != ELFINFO_MAG1) or \
      (elf_header.e_ident[ELFINFO_MAG2_INDEX] != ELFINFO_MAG2) or \
      (elf_header.e_ident[ELFINFO_MAG3_INDEX] != ELFINFO_MAG3) or \
      (elf_header.e_ident[ELFINFO_CLASS_INDEX] != ELFINFO_CLASS_32) or \
      (elf_header.e_ident[ELFINFO_VERSION_INDEX] != ELFINFO_VERSION_CURRENT):
      return False
   else:
      return True

#----------------------------------------------------------------------------
# Helper functions to open a file and return a valid file object
#----------------------------------------------------------------------------
def OPEN(file_name, mode):
    try:
       fp = open(file_name, mode)
    except IOError:
       raise RuntimeError, "The file could not be opened: " + file_name

    # File open has succeeded with the given mode, return the file object
    return fp

#----------------------------------------------------------------------------
# return the parent path
#----------------------------------------------------------------------------
def GetParentPath(strPath):
    if not strPath:
        return None;

    lsPath = os.path.split(strPath);
    #print(lsPath);
    #print("lsPath[1] = %s" %lsPath[1]);
    if lsPath[1]:
        return lsPath[0];

    lsPath = os.path.split(lsPath[0]);
    return lsPath[0];

#----------------------------------------------------------------------------
# ELF Header Class
#----------------------------------------------------------------------------
class Elf32_Ehdr:
   # Structure object to align and package the ELF Header
   s = struct.Struct('16sHHIIIIIHHHHHH')

   def __init__(self, data):
      unpacked_data       = (Elf32_Ehdr.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.e_ident        = unpacked_data[0]
      self.e_type         = unpacked_data[1]
      self.e_machine      = unpacked_data[2]
      self.e_version      = unpacked_data[3]
      self.e_entry        = unpacked_data[4]
      self.e_phoff        = unpacked_data[5]
      self.e_shoff        = unpacked_data[6]
      self.e_flags        = unpacked_data[7]
      self.e_ehsize       = unpacked_data[8]
      self.e_phentsize    = unpacked_data[9]
      self.e_phnum        = unpacked_data[10]
      self.e_shentsize    = unpacked_data[11]
      self.e_shnum        = unpacked_data[12]
      self.e_shstrndx     = unpacked_data[13]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value

   def getPackedData(self):
      values = [self.e_ident,
                self.e_type,
                self.e_machine,
                self.e_version,
                self.e_entry,
                self.e_phoff,
                self.e_shoff,
                self.e_flags,
                self.e_ehsize,
                self.e_phentsize,
                self.e_phnum,
                self.e_shentsize,
                self.e_shnum,
                self.e_shstrndx
               ]

      return (Elf32_Ehdr.s).pack(*values)

#----------------------------------------------------------------------------
# secure load image header
#----------------------------------------------------------------------------
class TEE_UUID:

   # Structure object to align and package the TEE_UUID
   s = struct.Struct('IHH8b')

   def __init__(self, data):
      unpacked_data       = (TEE_UUID.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.timeLow        = unpacked_data[0]
      self.timeMid        = unpacked_data[1]
      self.timeHiAndVersion = unpacked_data[2]
      self.clockSeqAndNode  = unpacked_data[3]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value

   def getPackedData(self):
      values = [self.timeLow,
                self.timeMid,
                self.timeHiAndVersion,
                self.clockSeqAndNode,
               ]

      return (TEE_UUID.s).pack(*values)

#----------------------------------------------------------------------------
# Manifest
#----------------------------------------------------------------------------
class Manifest:

   # Structure object to align and package the Manifest
   s = struct.Struct('IIIIII100sI128s')

   def __init__(self, data):
      unpacked_data       = (Manifest.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.single_instance = unpacked_data[0]
      self.multi_session  = unpacked_data[1]
      self.multi_command  = unpacked_data[2]
      self.heap_size      = unpacked_data[3]
      self.stack_size     = unpacked_data[4]
      self.instancekeepalive = unpacked_data[5]
      self.service_name = unpacked_data[6]
      self.service_name_len = unpacked_data[7]
      self.reserve = unpacked_data[8]

   def printValues(self):
      print "--------Dump manifest----------"
      for attr, value in self.__dict__.iteritems():
         print attr, ':', value

   def getPackedData(self):
      values = [self.single_instance,
                self.multi_session,
                self.multi_command,
                self.heap_size,
                self.stack_size,
                self.instancekeepalive,
                self.service_name,
                self.service_name_len,
                self.reserve,
               ]

      return (Manifest.s).pack(*values)


#----------------------------------------------------------------------------
# verify property name in manifest file
#----------------------------------------------------------------------------
def verify_property_name(strLine):
    #print 'verify property name'
    alphas = string.letters + string.digits
    cont = alphas + '-' + '_' + '.'
    if len(strLine) > 1:
        if strLine[0] not in alphas:
            print 'invalid first letter in property name'
            return False
        else:
            for otherchar in strLine[1:]:
                if otherchar not in cont:
                    print 'invalid char in property name'
                    return False
    else:
        print 'invalid property name'
        return False

    return True

#----------------------------------------------------------------------------
# verify property value in manifest file
#----------------------------------------------------------------------------
def verify_property_value(strLine):
    #print 'verify property value'
    filt_letter = chr(0) + chr(10) +chr(13)
    for thechar in strLine:
        if thechar in filt_letter:
            print 'invalid letter in prop value'
            return False
    return True

#----------------------------------------------------------------------------
# remove tabs and space in property value
#----------------------------------------------------------------------------
def trailing_space_tabs(strLine):
    #print 'trailing space tabs in value head and trail'
    #space_tabs = '    '+' '
    space_tabs = chr(9) + chr(32) +chr(160)
    space_tabs_newlines = space_tabs + chr(10) +chr(13)
    #print 'tab:'+space_tabs

    #print 'str in: '+strLine
    index = 0
    for thechar in strLine:
        if thechar in space_tabs:
            index += 1
        else:
            break
    headvalue = strLine[index:]

    strlen = len(headvalue)

    #save last newline
    #newline = headvalue[index]
    strlen -= 1
    #print 'str len: '+str(strlen)

    while strlen > 0:
        if headvalue[strlen] in space_tabs_newlines:
            strlen -= 1
        else:
            break

    #print 'str len: '+str(strlen)
    strRet = headvalue[0:strlen+1] + chr(10)
    #print 'str ret: '+strRet

    return strRet


def initManifestValue(manifest_val):
    #manifest default
    manifest_val.single_instance = 1
    manifest_val.multi_session = 0
    manifest_val.multi_command = 0
    manifest_val.instancekeepalive = 0
    manifest_val.heap_size = 65536
    manifest_val.stack_size = 4096
    manifest_val.service_name = 'default_service_name'

    return manifest_val

def parseManifestTxt(maniFileDir):
    manifest_val = Manifest('\0'*256)
    uuid_val = TEE_UUID('\0' * 16)
    maniFp = OPEN(maniFileDir, 'r')

    print 'manifest file[%s]' % maniFileDir
    for eachLine in maniFp:
        print eachLine
        index = eachLine.find(':', 1, len(eachLine))

        prop_name = eachLine[0:index] #no ':'
        prop_name_t = eachLine[0:index+1] #with ':'
        prop_value_t = eachLine[index+1:]
        #print 'name is :'+str(prop_name) + '; value is :'+str(prop_value_t)

        prop_value = trailing_space_tabs(prop_value_t)
        prop_len = len(prop_value)
        prop_value_v = prop_value[0:prop_len-1]# mv last letter
        #print 'prop value_v: ' + prop_value_v

        if verify_property_name(prop_name) is False:
            print 'manifest format invalid, please check it'
            return (False, 0, 0, 0, 0)

        if verify_property_value(prop_value_v) is False:
            print 'manifest format invalid, please check it'
            return (False, 0, 0, 0, 0)

        # name:value to lowcase, and parse manifest
        prop_name_low = prop_name.lower()
        #print "name lower: "+prop_name_low
        if cmp('gpd.ta.appid', prop_name_low) == 0:
            #print "compare name is srv id"
            uuid_val = uuid.UUID(prop_value_v)
            uuid_val_flag = 0
            #print 'uuid str'+ str(uuid_val)
            #print 'val fields'+ str(uuid_val.fields)

        elif cmp('gpd.ta.singleinstance', prop_name_low) == 0:
            prop_value_low = prop_value_v.lower()
            if cmp('true', prop_value_low) == 0:
                manifest_val.single_instance = 1;
            elif cmp('false', prop_value_low) == 0:
                manifest_val.single_instance = 0;
            else:
                print 'single_instance value error!'

        elif cmp('gpd.ta.multisession', prop_name_low) == 0:
            prop_value_low = prop_value_v.lower()
            if cmp('true', prop_value_low) == 0:
                manifest_val.multi_session = 1;
            elif cmp('false', prop_value_low) == 0:
                manifest_val.multi_session = 0;
            else:
                print 'multi_session value error!'

        elif cmp('gpd.ta.multicommand', prop_name_low) == 0:
            prop_value_low = prop_value_v.lower()
            if cmp('true', prop_value_low) == 0:
                manifest_val.multi_command = 1;
            elif cmp('false', prop_value_low) == 0:
                manifest_val.multi_command = 0;
            else:
                print 'multi_command value error!'

        elif cmp('gpd.ta.instancekeepalive', prop_name_low) == 0:
            prop_value_low = prop_value_v.lower()
            if cmp('true', prop_value_low) == 0:
                manifest_val.instancekeepalive = 1;
            elif cmp('false', prop_value_low) == 0:
                manifest_val.instancekeepalive = 0;
            else:
                print 'instancekeepalive value error!'

        elif cmp('gpd.ta.datasize', prop_name_low) == 0:
            manifest_val.heap_size = int(prop_value_v)

        elif cmp('gpd.ta.stacksize', prop_name_low) == 0:
            manifest_val.stack_size = int(prop_value_v)

        elif cmp('gpd.ta.service_name', prop_name_low) == 0:
            manifest_val.service_name = prop_value_v
            manifest_val.service_name_len = len(prop_value_v)

        else:
            print 'invalid prop name %s' % prop_name_t

    maniFp.close()

    return (manifest_val, uuid_val, uuid_val_flag)


def pack_ta_mainfest(elf_file, manifest_file):
    print "elf_file[%s]" % elf_file
    print "manifest_file[%s]" % manifest_file

    elf_parent_path = GetParentPath(elf_file)
    manifest_val = Manifest('\0'*256)
    uuid_val = TEE_UUID('\0' * 16)
    uuid_val_flag = 1
    manifest_val = initManifestValue(manifest_val)
    (manifest_val, uuid_val, uuid_val_flag) = parseManifestTxt(manifest_file)

    if uuid_val_flag == 1:
        print "manifest verify erro, no uuid"
        return

    manifest_val.printValues()
    print "uuid[%s]" % uuid_val

    # Verify ELF header information
    elf_fp = OPEN(elf_file, 'rb')
    elf_hd_buf = elf_fp.read(ELF_HDR_SIZE)
    elf_header = Elf32_Ehdr(elf_hd_buf)
    if verify_elf_header(elf_header) is False:
       raise RuntimeError, "ELF file failed verification: " + elf_file

    # write elf file
    elf_fp.seek(0)
    elf_sz = os.path.getsize(elf_file)
    elf_file_buf = elf_fp.read(elf_sz)
    elf_fp.close()

    output_file = elf_parent_path + '/' + str(uuid_val) + '.bin'
    print "output_file[%s]" % output_file
    output_fp = OPEN(output_file, 'wb')
    output_fp.write(uuid_val.bytes_le)
    output_fp.write(manifest_val.getPackedData())
    output_fp.write(elf_file_buf)
    output_fp.close()
    return

if __name__ == '__main__':
    argvs = sys.argv
    elf_file = argvs[1]
    manifest_file = argvs[2]
    pack_ta_mainfest(elf_file, manifest_file)
