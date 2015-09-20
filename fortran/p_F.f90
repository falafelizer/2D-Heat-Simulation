program p_F
  !use updateMap

  implicit none

  integer::argument
  character*30 basename filename input_file output_freq_char
  !character(30)::filename
  !character(30)::input_file
  !character(30)::output_freq_char
  character*10 x_pos_readin y_pos_readin
  !character(10)::y_pos_readin
  character*1 x_pos_str y_pos_str
  integer::i, j, k, t, x, y
  integer::num_timesteps
  integer::x_size, y_size
  integer::x_max, y_max, hold
  integer::x_pos, y_pos
  integer::output_freq
  real::temp, alpha
  real, dimension(2), allocatable::heatmap(:,:)
  integer, dimension(2), allocatable::holdmap(:,:)

  ! ----------------------------------------

  ! Collect arguments
  argument = NARGS()

  if (argument /= 4) then
   print*, "Please provide the correct number of arguments (4)"
  end if

  if (argument == 4) then
    call GETARG(1, input_file)
    call GETARG(2, output_freq_char)
      read(output_freq_char, *)output_freq
    call GETARG(3, basename)
  end if

  ! ----------------------------------------

  ! Allocate arrays
  allocate(heatmap(x_size, y_size))
  allocate(holdmap(x_size, y_size))

  ! ----------------------------------------

  ! Begin reading values from input file
  OPEN(UNIT=10, FILE=input_file, STATUS='old')

  READ(10, *)x_size, y_size, alpha, hold

  x_max = (x_size - 1)
  y_max = (y_max - 1)

  ! ---------------------------------------

  ! Read in values until end of file
  do while (k >= 0)
    READ(input_file, *, IOSTAT = k)

    ! Read in values
    READ(10, *)x_pos_readin, y_pos_readin, temp, hold

    x_pos_readin_str = x_pos_readin(0)
    y_pos_str = y_pos_readin(0)


    if ((x_pos_str == '*').and.(y_pos_str == '*')) then
      do i = 1, x_size, 1
        do j = 1, y_size, 1
          heatmap(0, i, j) = temp
          holdmap(0, i, j) = hold
        end do
      end do
    end if
    
    if((x_pos_str == '*').and.(y_pos_str /= '*')) then
      do i = 1, x_size, 1
        do j = 1, y_size, 1
          read(y_pos_str, *)y_pos
          heatmap(0, i, y_pos) = temp
          holdmap(0, i, y_pos) = hold
        end do
      end do
    end if

    if((x_pos_str /= '*').and.(y_pos_str == '*')) then
      do i = 1, x_size, 1
        do j = 1, y_size, 1
          read(x_pos_str, *)x_pos
          heatmap(0, x_pos, j) = temp
          holdmap(0, x_pos, j) = hold
        end do
      end do
    end if

    if((x_pos_str /= '*').and.(y_pos_str /= '*')) then
      do i = 1, x_size, 1
        do j = 1, y_size, 1
          read(x_pos_str, *)x_pos
          read(y_pos_str, *)y_pos
          heatmap(0, x_pos, y_pos) = temp
          holdmap(0, x_pos, y_pos) = hold
        end do
      end do
    end if
  end do

  close(10)

! ------------------------------------------------

! Compute temperatures!

do t = 1, t <= num_timesteps, 1
  
  ! Corners
  ! Top left corner
  heatmap(mod(t,2), 0, 0) = heatmap(mod((t-1),2), 0, 0) + ((holdmap(0, 0, 0)-1)*-1)*alpha*(heatmap(mod((t-1),2), (0+1), 0) + heatmap(mod((t-1),2), 0, (0+1)) + heatmap(mod((t-1),2), (0+1), (0+1)) - 3*heatmap(mod((t-1),2), 0, 0))

  ! Top right corner
  heatmap(mod(t,2), 0, 0) = heatmap(mod((t-1),2), 0, y_max) + ((holdmap(0, 0, y_max)-1)*-1)*alpha*(heatmap(mod((t-1),2), 0, y_max-1) + heatmap(mod((t-1),2), 0+1, y_max-1) + heatmap(mod((t-1),2), 0+1, y_max) - 3*heatmap(mod((t-1),2), 0, y_max))

  ! Bottom right corner
  heatmap(mod(t,2), x_max, 0) = heatmap(mod((t-1),2), x_max, 0) + ((holdmap(0, x_max, 0)-1)*-1)*alpha*(heatmap(mod((t-1),2), x_max-1, 0) + heatmap(mod((t-1),2), x_max, 0+1) + heatmap(mod((t-1),2), x_max-1, 0+1) - 3*heatmap(mod((t-1),2), x_max, 0))

  ! Bottom left corner
  heatmap(mod(t,2), x_max, y_max) = heatmap(mod((t-1),2), x_max, y_max) + ((holdmap(0, x_max, 0)-1)*-1)*alpha*(heatmap(mod((t-1),2), x_max-1, y_max) + heatmap(mod((t-1),2), x_max, y_max-1) + heatmap(mod((t-1),2), x_max-1, y_max-1) - 3*heatmap(mod((t-1),2), x_max, y_max))


  ! Sides
  ! Left & right
  do j = 1, y_max, 1

    ! Left
    heatmap(mod(t, 2), 0, j) = heatmap(mod((t-1), 2), 0, j) + ((holdmap(0, 0, j)-1)*-1)*alpha*(heatmap(mod((t-1), 2), 0, j-1) + heatmap(mod((t-1), 2), 0+1, j-1) + heatmap(mod((t-1), 2), 0+1, j) + heatmap(mod((t-1), 2), 0, j+1) + heatmap(mod((t-1), 2), 0+1, j+1) - 5*heatmap(mod((t-1), 2), 0, j))

    ! Right
    heatmap(mod(t, 2), 0, j) = heatmap(mod((t-1), 2), 0, j) + ((holdmap(0, 0, j)-1)*-1)*alpha*(heatmap(mod((t-1), 2), 0, j-1) + heatmap(mod((t-1), 2), 0+1, j-1) + heatmap(mod((t-1), 2), 0+1, j) + heatmap(mod((t-1), 2), 0, j+1) + heatmap(mod((t-1), 2), 0+1, j+1) - 5*heatmap(mod((t-1), 2), 0, j))

  end do

  ! Top & bottom
  do i = 1, x_max, 1

    ! Top
    heatmap(mod(t, 2), i, 0) = heatmap(mod((t-1), 2), i, 0) + ((holdmap(0, i, 0)-1)*-1)*alpha*(heatmap(mod((t-1), 2), (i-1), 0) + heatmap(mod((t-1), 2), i+1, 0) + heatmap(mod((t-1), 2), i-1, (0+1)) + heatmap(mod((t-1), 2), i, (0+1)) + heatmap(mod((t-1), 2), x+1, 0+1) - 5*heatmap(mod((t-1), 2), i, 0))

    ! Bottom
    heatmap(mod(t, 2), 0, j) = heatmap(mod((t-1), 2), i, y_max) + ((holdmap(0, i, y_max)-1)*-1)*alpha*(heatmap(mod((t-1), 2), i-1, y_max-1) + heatmap(mod((t-1), 2), i, y_max-1) + heatmap(mod((t-1), 2), i+1, y_max-1) + heatmap(mod((t-1), 2), i-1, y_max) + heatmap(mod((t-1), 2), i+1, y_max) - 5*heatmap(mod((t-1), 2), i, y_max))

  end do


  ! Middle
  do i = 1, x_max, 1
    do j = 1, y_max, 1
      heatmap(mod(t, 2), i, j) = heatmap(mod((t-1), 2), i, j) + ((holdmap(0, i, j)-1)*-1)*alpha*(heatmap(mod((t-1), 2), i-1, j-1) + heatmap(mod((t-1), 2), i, j-1) + heatmap(mod((t-1), 2), i+1, j-1) + heatmap(mod((t-1), 2), i+1, j) + heatmap(mod((t-1), 2), i-1, j+1) + heatmap(mod((t-1), 2), i, j+1) + heatmap(mod((t-1), 2), i+1, j+1) - 8*heatmap(mod((t-1), 2), i, y_max))
    end do
  end do


    if(mod(t,output_freq)==0) then
      write(filename, '(A,A,I0.4,A)'), trim(basename), "_", t, ".dat"
      open(unit=t, file=filename)
      do i = 1, x_size, 1
        do j = 1, y_size, 1
          write(t,*) i, j, heatmap(mod(t, 2), i, j)
        end do
      end do
    end if

end do

!close(t)
    

! Deallocate
deallocate(heatmap)
deallocate(holdmap)

end program 
