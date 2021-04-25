import React from 'react'
import { connect } from 'react-redux'
import Profile from './Profile'
import { getUserProfile } from '../../redux/profile-reducer'
import { Redirect, withRouter } from 'react-router'

class ProfileContainer extends React.Component {
  componentDidMount() {
    let userId = this.props.match.params.userId
    if (!userId) userId = 2
    this.props.getUserProfile(userId)
  }
  render() {
    if (!this.props.isAuth) return <Redirect to='/Login' />
    return (
      <div>
        <Profile {...this.props} />
      </div>
    )
  }
}

let mapStateToProps = state => ({
  profile: state.profilePage.profile,
  isAuth: state.auth.isAuth
})

// Закидывает данные из урла: match, location, history, ...
let withUrlDataContainerComponent = withRouter(ProfileContainer)

export default connect(mapStateToProps, { getUserProfile })(
  withUrlDataContainerComponent
)
