import * as axios from 'axios'

const instance = axios.create({
  withCredentials: true,
  baseURL: 'https://social-network.samuraijs.com/api/1.0/',
  headers: {
    'API-KEY': 'c4b4c099-00c8-43ae-b1f9-65ae19e7d6ae'
  }
})

export const usersAPI = {
  getUsers(currentPage = 1, pageSize = 10) {
    return instance
      .get(`users?page=${currentPage}&count=${pageSize}`)
      .then(response => response.data)
  }
}

export const getUsers2 = (currentPage = 1, pageSize = 10) => {
  return instance.get(`follow?id=`).then(response => response.data)
}
